#ifndef __PROGRAM_PATH_UTILS__
#define __PROGRAM_PATH_UTILS__

#include <string>
#include <boost/locale.hpp>
#include <boost/filesystem.hpp>

#include <windows.h>

#define OS_MAX_PATH 32768

// ��ȡ��������·��
std::string get_self_file_path();

// ��ȡ�����������ڵ��ļ���·��
std::string get_self_dir_path();

// ��ȡ����Ŀ¼
std::string get_work_dir();

// ���ù���Ŀ¼
bool set_work_dir(const std::string& path);


#endif // __PROGRAM_PATH_UTILS__