
#pragma once
//ref to : http://www.koders.com/cpp/fid6D66CEDDC53FEFF5C6A63D4CA5E0AE51402C32C7.aspx
template<class T>
class ComPtr
{
public:
	ComPtr();
	ComPtr(T* _p);
	ComPtr(const ComPtr<T>& _p);
	~ComPtr();

	inline ComPtr<T>& operator=(T* _p);
	inline ComPtr<T>& operator=(const ComPtr<T>& arg);

	T* operator->()const;
	inline operator T*()const;

	inline T& operator*()const;
	inline T** operator&();

	inline T* GetPointer(){return p;}
protected:
	inline void Release();
	inline void AddRef();
private:
	T* p;
};


template<class T>
ComPtr<T>::ComPtr():
p(NULL)
{ }

template<class T>
ComPtr<T>::ComPtr(T* _p):
p(_p)
{
	AddRef();
}

template<class T>
ComPtr<T>::ComPtr(const ComPtr<T>& _p):
p(_p.p)
{
	AddRef();
}

template<class T>
inline ComPtr<T>& ComPtr<T>::operator = (T* _p)
{
	Release();
	p = _p;
	AddRef();
	return *this;
}

template<class T>
ComPtr<T>::~ComPtr()
{
	Release();
}

template<class T>
inline ComPtr<T>& ComPtr<T>::operator = (const ComPtr<T>& arg)
{
	Release();
	p = arg.p;
	AddRef();
	return *this;
}

template<class T>
inline T* ComPtr<T>::operator->()const
{
	return p;
}

template<class T>
inline ComPtr<T>::operator T* () const
{
	return p;
}

template<class T>
inline T& ComPtr<T>::operator *()const
{
	return *p;
}

template<class T>
inline void ComPtr<T>::Release()
{
	if(p)p->Release();
}

template<class T>
inline void ComPtr<T>::AddRef()
{
	if(p)p->AddRef();
}

template<class T>
inline T** ComPtr<T>::operator &()
{
	return &p;
}
