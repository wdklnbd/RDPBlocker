#ifndef __SYSTEM_EVENT_LOG_CLASS__
#define __SYSTEM_EVENT_LOG_CLASS__

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <boost/locale.hpp>
#include "logger.h"
#include "handle_wrapper.h"
#include "boost_xml_utils.h"

#include <windows.h>
#include <winevt.h>

#pragma comment(lib, "wevtapi.lib")


template <typename HANDLE>
class EventLogHandleTraits
{
public:
    static constexpr HANDLE InvalidValue() {
        return NULL;
    }

    static void Close(HANDLE value)
    {
        EvtClose(value);
    }
};
typedef HandleWrapper<EVT_HANDLE, EventLogHandleTraits<EVT_HANDLE> > EventLogHandleWrapper;


class SubscribeSystemEvent
{
public:
    EventLogHandleWrapper m_handle_subscription;
    NullKernelHandleWrapper m_handle_signal_event;

    // ����RDP��¼ʧ���¼�
    bool SubscribeRDPAuthFailedEvent();
    // ����ϵͳ�¼�
    bool Subscribe(const std::string& path, const std::string& query);
    // ��ȡ�¼���¼����Ҫ�Ļ�������С
    DWORD GetEventLogRecordSize(EVT_HANDLE hEvent, DWORD& dwBufferSize);
    // ��ȡ�¼���¼
    DWORD GetEventLogRecord(EVT_HANDLE hEvent, std::string& output);
    // ��ȡ������¼�����浽vector
    bool StoreEventLogResults(std::vector<std::string>& vt_results);
    // �����ź�
    bool CreateSignal();
    // �ȴ��ź�
    bool WaitSignal();
    // �����ź�
    bool SetSignal();
    // �����ź�
    bool ResetSignal();
};

// ��XML�����е�Event.EventData���µ�������Ŀ��ӵ�map
bool GetLogEventDataToMap(const std::string& xml_data, std::map<std::string, std::string>& attr);
#endif //__SYSTEM_EVENT_LOG_CLASS__