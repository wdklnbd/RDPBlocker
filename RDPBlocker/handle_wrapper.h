#ifndef __OS_HANDLE_WRAPPER_CLASS__
#define __OS_HANDLE_WRAPPER_CLASS__

#include <cstddef>
#include <windows.h>

template <typename HandleType,typename Traits>
class HandleWrapper
{
private:
    typedef HandleWrapper<HandleType, Traits> HandleWrapperType;
    HandleType m_Handle;

public:
    HandleWrapper()
        :m_Handle(Traits::InvalidValue())
    {
    }

    HandleWrapper(const HandleType value)
        :m_Handle(value)
    {
    }

    ~HandleWrapper()
    {
        Close();
    }

    void Attach(const HandleType value)
    {
        m_Handle = value;
    }

    void Detach()
    {
        m_Handle = Traits::InvalidValue();
    }
    
    void Close()
    {
        if (m_Handle != Traits::InvalidValue())
        {
            Traits::Close(m_Handle);
            m_Handle = Traits::InvalidValue();
        }
    }

    HandleType Get() const
    {
        return m_Handle;
    }

    void Set(const HandleType value)
    {
        m_Handle = value;
    }

    bool IsVaild() const
    {
        return (m_Handle != Traits::InvalidValue());
    }

    bool IsInvalid() const 
    {
        return (m_Handle == Traits::InvalidValue());
    }

    operator bool() const {
        return (m_Handle != Traits::InvalidValue());
    }

    bool operator !() const {
        return (m_Handle == Traits::InvalidValue());
    }

    operator HandleType() const {
        return m_Handle;
    }

    // ����Ӿ������
    HandleWrapper<HandleType, Traits>& operator =(const HandleType& src)
    {
        Close();
        Attach(src);
        return *this;
    }

    // ת�ƹ���
    HandleWrapper(HandleWrapper<HandleType, Traits>&& src)
    {
        m_Handle = src.m_Handle;
        src.m_Handle = Traits::InvalidValue();
    }

    // ת�ƿ���
    HandleWrapper<HandleType, Traits>& operator =(HandleWrapper<HandleType, Traits>& src)
    {
        m_Handle = src.m_Handle;
        src.m_Handle = Traits::InvalidValue();
        return *this;
    }

/*
private:
    // ��ֹ���쿽��
    HandleWrapper(const HandleWrapper<HandleType, Traits>&) = delete;
    // ��ֹ���ƿ���
    HandleWrapper<HandleType, Traits>& operator =(const HandleWrapper<HandleType, Traits>&) = delete;
*/
};

template <typename HANDLE>
class KernelHandleTraits
{
public:
    static constexpr HANDLE InvalidValue(){
        return INVALID_HANDLE_VALUE;
    }

    static void Close(HANDLE value)
    {
        CloseHandle(value);
    }
};

template <typename HANDLE>
class NullKernelHandleTraits
{
public:
    static constexpr HANDLE InvalidValue() {
        return NULL;
    }

    static void Close(HANDLE value)
    {
        CloseHandle(value);
    }
};

/*
// For example:
HandleWrapper<HANDLE, KernelHandleTraits<HANDLE> > hFile(CreateFile(...));
HandleWrapper<HANDLE, NullKernelHandleTraits<HANDLE> > hThread(CreateThread(...));
*/

typedef HandleWrapper<HANDLE, KernelHandleTraits<HANDLE> > KernelHandleWrapper;
typedef HandleWrapper<HANDLE, NullKernelHandleTraits<HANDLE> > NullKernelHandleWrapper;

/*
// Used typedef example:
KernelHandleWrapper hFile(CreateFile(...));
NullKernelHandleWrapper hThread(CreateThread(...));
*/

#endif //__OS_HANDLE_WRAPPER_CLASS__