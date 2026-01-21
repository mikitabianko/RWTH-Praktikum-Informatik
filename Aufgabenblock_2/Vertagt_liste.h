#ifndef VERTAGT_LISTE_H
#define VERTAGT_LISTE_H

#include <list>
#include <memory>
#include "Vertagt_aktion.h"

namespace vertagt {

template <typename T>
class VListe {
private:
    std::list<T> p_objekte;
    std::list<std::unique_ptr<VAktion<T>>> p_aktionen;

    friend class VAktion<T>;
    friend class VPushFront<T>;
    friend class VPushBack<T>;
    friend class VErase<T>;

public:
    VListe() = default;
    ~VListe() = default;

    using iterator = typename std::list<T>::iterator;
    using const_iterator = typename std::list<T>::const_iterator;

    iterator begin() { return p_objekte.begin(); }
    iterator end() { return p_objekte.end(); }
    const_iterator begin() const { return p_objekte.begin(); }
    const_iterator end() const { return p_objekte.end(); }

    bool empty() const { return p_objekte.empty(); }

    void push_front(T obj) {
        p_aktionen.push_back(std::make_unique<VPushFront<T>>(std::move(obj), *this));
    }

    void push_back(T obj) {
        p_aktionen.push_back(std::make_unique<VPushBack<T>>(std::move(obj), *this));
    }

    void erase(iterator it) {
        p_aktionen.push_back(std::make_unique<VErase<T>>(it, *this));
    }

    void vAktualisieren() {
        for (auto& aktion : p_aktionen) {
            aktion->vAusfuehren();
        }
        p_aktionen.clear();
    }

    void clear() {
        vAktualisieren();
        p_objekte.clear();
    }
};

} 

#endif