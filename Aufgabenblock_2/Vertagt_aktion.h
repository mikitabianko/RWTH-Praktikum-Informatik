#ifndef VERTAGT_AKTION_H
#define VERTAGT_AKTION_H

namespace vertagt {

template <typename T>
class VListe;

template <typename T>
class VAktion {
protected:
    VListe<T>& p_pListe;
public:
    VAktion(VListe<T>& liste) : p_pListe(liste) {}
    virtual ~VAktion() = default;
    virtual void vAusfuehren() = 0;
};

template <typename T>
class VPushFront : public VAktion<T> {
    T p_obj;
public:
    VPushFront(T obj, VListe<T>& liste) : VAktion<T>(liste), p_obj(std::move(obj)) {}
    void vAusfuehren() override {
        this->p_pListe.p_objekte.push_front(std::move(p_obj));
    }
};

template <typename T>
class VPushBack : public VAktion<T> {
    T p_obj;
public:
    VPushBack(T obj, VListe<T>& liste) : VAktion<T>(liste), p_obj(std::move(obj)) {}
    void vAusfuehren() override {
        this->p_pListe.p_objekte.push_back(std::move(p_obj));
    }
};

template <typename T>
class VErase : public VAktion<T> {
    typename std::list<T>::iterator p_it;
public:
    VErase(typename std::list<T>::iterator it, VListe<T>& liste) : VAktion<T>(liste), p_it(it) {}
    void vAusfuehren() override {
        this->p_pListe.p_objekte.erase(p_it);
    }
};

} 

#endif