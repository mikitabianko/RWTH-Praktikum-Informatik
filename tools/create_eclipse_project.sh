#!/usr/bin/env bash
set -euo pipefail

usage() {
	cat <<'USAGE'
Usage:
  ./create_eclipse_project.sh PROJECT_NAME [options]

Creates a C++ Eclipse CDT project in this repository, using the existing
projects as metadata templates and the matching folder in Vorlagen as sources.

Examples:
  ./create_eclipse_project.sh Versuch06
  ./create_eclipse_project.sh Versuch07 --empty
  ./create_eclipse_project.sh Versuch10 --source Vorlagen/Versuch09
  ./create_eclipse_project.sh Versuch10 --meta-template Versuch05

Options:
  --source DIR          Copy starter files from DIR.
  --empty               Create only Eclipse project metadata, without sources.
  --meta-template DIR   Copy Eclipse metadata from DIR. Default: first existing
                        project with .project, .cproject and .settings.
  --dry-run             Show what would be created without writing files.
  -h, --help            Show this help.
USAGE
}

die() {
	printf 'Error: %s\n' "$*" >&2
	exit 1
}

script_dir() {
	CDPATH= cd -- "$(dirname -- "$0")" && pwd
}

resolve_path() {
	local path=$1

	if [[ $path == /* ]]; then
		printf '%s\n' "$path"
	else
		printf '%s/%s\n' "$ROOT_DIR" "$path"
	fi
}

has_eclipse_metadata() {
	local dir=$1

	[[ -f $dir/.project && -f $dir/.cproject && -d $dir/.settings ]]
}

choose_meta_template() {
	local candidate

	for candidate in Versuch05 Versuch04 Versuch03 Versuch02Teil1 Versuch01Teil1 Aufgabenblock_1 Aufgabenblock_2; do
		candidate=$ROOT_DIR/$candidate
		if has_eclipse_metadata "$candidate"; then
			printf '%s\n' "$candidate"
			return 0
		fi
	done

	while IFS= read -r candidate; do
		candidate=${candidate%/.project}
		if has_eclipse_metadata "$candidate"; then
			printf '%s\n' "$candidate"
			return 0
		fi
	done < <(find "$ROOT_DIR" -maxdepth 2 -name .project -print | sort)

	return 1
}

infer_source_dir() {
	local name=$1
	local candidate

	candidate=$ROOT_DIR/Vorlagen/$name
	if [[ -d $candidate ]]; then
		printf '%s\n' "$candidate"
		return 0
	fi

	if [[ $name =~ ^Versuch([0-9]+)Teil([0-9]+)$ ]]; then
		candidate=$ROOT_DIR/Vorlagen/Versuch${BASH_REMATCH[1]}_Teil${BASH_REMATCH[2]}
		if [[ -d $candidate ]]; then
			printf '%s\n' "$candidate"
			return 0
		fi
	fi

	if [[ $name =~ ^Versuch([0-9]+)_Teil([0-9]+)$ ]]; then
		candidate=$ROOT_DIR/Vorlagen/Versuch${BASH_REMATCH[1]}_Teil${BASH_REMATCH[2]}
		if [[ -d $candidate ]]; then
			printf '%s\n' "$candidate"
			return 0
		fi
	fi

	return 1
}

copy_source_contents() {
	local source_dir=$1
	local target_dir=$2

	find "$source_dir" -mindepth 1 -maxdepth 1 \
		! -name .project \
		! -name .cproject \
		! -name .settings \
		! -name .gitignore \
		! -name Debug \
		! -name Release \
		-exec cp -R {} "$target_dir" \;
}

extract_project_name() {
	local project_file=$1
	local name

	name=$(sed -n 's:.*<name>\([^<]*\)</name>.*:\1:p' "$project_file" | head -n 1)
	[[ -n $name ]] || return 1
	printf '%s\n' "$name"
}

write_project_metadata() {
	local project_name=$1
	local meta_template=$2
	local target_dir=$3
	local old_name

	old_name=$(extract_project_name "$meta_template/.project" || basename "$meta_template")

	awk -v project_name="$project_name" '
		!changed && $0 ~ /^[[:space:]]*<name>[^<]*<\/name>[[:space:]]*$/ {
			sub(/<name>[^<]*<\/name>/, "<name>" project_name "</name>")
			changed = 1
		}
		{ print }
	' "$meta_template/.project" > "$target_dir/.project"

	sed \
		-e "s|workspace_loc:/${old_name}|workspace_loc:/${project_name}|g" \
		-e "s|workspacePath=\"/${old_name}\"|workspacePath=\"/${project_name}\"|g" \
		-e "s|<project id=\"${old_name}\.|<project id=\"${project_name}.|g" \
		"$meta_template/.cproject" > "$target_dir/.cproject"

	mkdir -p "$target_dir/.settings"
	find "$meta_template/.settings" -mindepth 1 -maxdepth 1 -exec cp -R {} "$target_dir/.settings" \;

	if [[ -f $meta_template/.gitignore ]]; then
		cp "$meta_template/.gitignore" "$target_dir/.gitignore"
	else
		printf '/Debug/\n/Release/\n' > "$target_dir/.gitignore"
	fi
}

ROOT_DIR=$(script_dir)
PROJECT_NAME=
SOURCE_DIR=
META_TEMPLATE=
EMPTY=0
DRY_RUN=0

while [[ $# -gt 0 ]]; do
	case $1 in
		--source)
			shift
			[[ $# -gt 0 ]] || die '--source requires a directory'
			SOURCE_DIR=$(resolve_path "$1")
			;;
		--empty)
			EMPTY=1
			;;
		--meta-template|--eclipse-template)
			shift
			[[ $# -gt 0 ]] || die '--meta-template requires a directory'
			META_TEMPLATE=$(resolve_path "$1")
			;;
		--dry-run)
			DRY_RUN=1
			;;
		-h|--help)
			usage
			exit 0
			;;
		-*)
			die "unknown option: $1"
			;;
		*)
			if [[ -n $PROJECT_NAME ]]; then
				die "unexpected argument: $1"
			fi
			PROJECT_NAME=$1
			;;
	esac
	shift
done

[[ -n $PROJECT_NAME ]] || {
	usage
	exit 1
}

[[ $PROJECT_NAME =~ ^[A-Za-z0-9_-]+$ ]] || die 'project name may contain only letters, numbers, underscores and hyphens'
[[ $EMPTY -eq 0 || -z $SOURCE_DIR ]] || die '--empty cannot be combined with --source'

TARGET_DIR=$ROOT_DIR/$PROJECT_NAME
[[ ! -e $TARGET_DIR ]] || die "target already exists: $TARGET_DIR"

if [[ -n $META_TEMPLATE ]]; then
	has_eclipse_metadata "$META_TEMPLATE" || die "metadata template is not an Eclipse CDT project: $META_TEMPLATE"
else
	META_TEMPLATE=$(choose_meta_template) || die 'could not find an existing Eclipse CDT project to use as metadata template'
fi

if [[ $EMPTY -eq 0 ]]; then
	if [[ -n $SOURCE_DIR ]]; then
		[[ -d $SOURCE_DIR ]] || die "source directory does not exist: $SOURCE_DIR"
	else
		SOURCE_DIR=$(infer_source_dir "$PROJECT_NAME") || die "no matching source folder found in Vorlagen; pass --source DIR or --empty"
	fi
fi

printf 'Project:       %s\n' "$PROJECT_NAME"
printf 'Target:        %s\n' "$TARGET_DIR"
printf 'Metadata from: %s\n' "$META_TEMPLATE"
if [[ $EMPTY -eq 1 ]]; then
	printf 'Sources:       none\n'
else
	printf 'Sources:       %s\n' "$SOURCE_DIR"
fi

if [[ $DRY_RUN -eq 1 ]]; then
	printf 'Dry run:       no files written\n'
	exit 0
fi

TMP_DIR=$(mktemp -d "${TMPDIR:-/tmp}/eclipse-project.XXXXXX")
cleanup() {
	if [[ -n ${TMP_DIR:-} && -d $TMP_DIR ]]; then
		rm -rf "$TMP_DIR"
	fi
}
trap cleanup EXIT

if [[ $EMPTY -eq 0 ]]; then
	copy_source_contents "$SOURCE_DIR" "$TMP_DIR"
fi

write_project_metadata "$PROJECT_NAME" "$META_TEMPLATE" "$TMP_DIR"
mv "$TMP_DIR" "$TARGET_DIR"
TMP_DIR=

printf 'Created Eclipse project: %s\n' "$TARGET_DIR"
