#ifndef __SINGLETON_H__
#define __SINGLETON_H__


template <class T>
class Singleton{
  public:
    static T* getInstance();
    static void freeInstance();


  protected:
    Singleton() {};
    ~Singleton() {};

  private:
    static T* instance_;

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};


template <class T>
inline T* Singleton<T>::getInstance(){
  if(instance_ == 0){
    instance_ = new T();
  }
  return instance_;
}


template <class T> 
inline void Singleton<T>::freeInstance(){
  delete instance_;
  instance_ = 0;
}

#endif //__SINGLETON_H__
