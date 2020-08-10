#pragma once

#include "stdafx.h"
#include <iostream>

using namespace std;

class CTransCoding
{
public:
	static wstring UTF8_To_UTF16(const string &source)
	{
		unsigned long len = MultiByteToWideChar(CP_UTF8, NULL, source.c_str(), -1, NULL, NULL);
		if (len == 0)
			return wstring();
		wchar_t *buffer = new wchar_t[len];
		MultiByteToWideChar(CP_UTF8, NULL, source.c_str(), -1, buffer, len);

		wstring dest(buffer);
		delete[] buffer;
		return dest;
	}

	static string UTF16_To_UTF8(const wstring &source)
	{
		unsigned long len = WideCharToMultiByte(CP_UTF8, NULL, source.c_str(), -1, NULL, NULL, NULL, NULL);
		if (len == 0)
			return string();
		char *buffer = new char[len];
		WideCharToMultiByte(CP_UTF8, NULL, source.c_str(), -1, buffer, len, NULL, NULL);

		string dest(buffer);
		delete[] buffer;
		return dest;
	}

	static std::string WStringToString(const std::wstring &str_in)
	{
		if (str_in.empty())
		{
			std::cout << "str_in is empty" << std::endl;
			return "";
		}

		// 获取待转换的数据的长度
		int len_in = WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)str_in.c_str(), -1, NULL, 0, NULL, NULL);
		if (len_in <= 0)
		{
			std::cout << "The result of WideCharToMultiByte is Invalid!" << std::endl;
			return "";
		}

		// 为输出数据申请空间
		std::string wstr_out;
		wstr_out.resize(len_in - 1, '\0');

		// 数据格式转换
		int to_result = WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)str_in.c_str(), -1, (LPSTR)wstr_out.c_str(), len_in, NULL, NULL);
		// 判断转换结果
		if (0 == to_result)
		{
			std::cout << "Can't transfer WString to String" << std::endl;
			return "";
		}
		return wstr_out;
	}

	static std::string ws2s(const std::wstring & src)
	{
		setlocale(LC_ALL, "");
		std::string res = "";

		size_t const mbs_len = wcstombs(NULL, src.c_str(), 0);
		
		std::vector<char> buffer(mbs_len + 1);

		wcstombs(&buffer[0], src.c_str(), buffer.size());

		res.assign(buffer.begin(), buffer.end() - 1);

		return res;
	}
	static wstring GBK_To_UTF16(const string &source)
	{
		enum { GB2312 = 936 };

		unsigned long len = MultiByteToWideChar(GB2312, NULL, source.c_str(), -1, NULL, NULL);
		if (len == 0)
			return wstring();
		wchar_t *buffer = new wchar_t[len];
		MultiByteToWideChar(GB2312, NULL, source.c_str(), -1, buffer, len);

		wstring dest(buffer);
		delete[] buffer;
		return dest;
	}

	static string UTF16_To_GBK(const wstring &source)
	{
		enum { GB2312 = 936 };

		unsigned long len = WideCharToMultiByte(GB2312, NULL, source.c_str(), -1, NULL, NULL, NULL, NULL);
		if (len == 0)
			return string();
		char *buffer = new char[len];
		WideCharToMultiByte(GB2312, NULL, source.c_str(), -1, buffer, len, NULL, NULL);

		string dest(buffer);
		delete[] buffer;
		return dest;
	}

	static string GBK_To_UTF8(const string &source)
	{
		enum { GB2312 = 936 };

		unsigned long len = MultiByteToWideChar(GB2312, NULL, source.c_str(), -1, NULL, NULL);
		if (len == 0)
			return string();
		wchar_t *wide_char_buffer = new wchar_t[len];
		MultiByteToWideChar(GB2312, NULL, source.c_str(), -1, wide_char_buffer, len);

		len = WideCharToMultiByte(CP_UTF8, NULL, wide_char_buffer, -1, NULL, NULL, NULL, NULL);
		if (len == 0)
		{
			delete[] wide_char_buffer;
			return string();
		}
		char *multi_byte_buffer = new char[len];
		WideCharToMultiByte(CP_UTF8, NULL, wide_char_buffer, -1, multi_byte_buffer, len, NULL, NULL);

		string dest(multi_byte_buffer);
		delete[] wide_char_buffer;
		delete[] multi_byte_buffer;
		return dest;
	}

	static string UTF8_To_GBK(const string &source)
	{
		enum { GB2312 = 936 };

		unsigned long len = MultiByteToWideChar(CP_UTF8, NULL, source.c_str(), -1, NULL, NULL);
		if (len == 0)
			return string();
		wchar_t *wide_char_buffer = new wchar_t[len];
		MultiByteToWideChar(CP_UTF8, NULL, source.c_str(), -1, wide_char_buffer, len);

		len = WideCharToMultiByte(GB2312, NULL, wide_char_buffer, -1, NULL, NULL, NULL, NULL);
		if (len == 0)
		{
			delete[] wide_char_buffer;
			return string();
		}
		char *multi_byte_buffer = new char[len];
		WideCharToMultiByte(GB2312, NULL, wide_char_buffer, -1, multi_byte_buffer, len, NULL, NULL);

		string dest(multi_byte_buffer);
		delete[] wide_char_buffer;
		delete[] multi_byte_buffer;
		return dest;
	}

	static wstring UTF8ToUnicode(const string & s)
	{
		wstring result;
		int n = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, NULL, 0);
		wchar_t * buffer = new wchar_t[n];

		::MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, buffer, n);

		result = buffer;
		delete[] buffer;

		return result;
	}


	static std::string WChar2Ansi(LPCWSTR pwszSrc)
	{
		int nLen = 0;
		nLen = WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, NULL, 0, NULL, NULL);
		if (nLen <= 0)
			return std::string("");

		char* pszDst = new char[nLen];
		if (NULL == pszDst)
			return std::string("");

		WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, pszDst, nLen, NULL, NULL);
		pszDst[nLen - 1] = 0;
		std::string strTemp(pszDst);
		delete[] pszDst;

		return strTemp;
	}

	static wstring UTF8_To_Unicode(string szUtf8)
	{
		int len = MultiByteToWideChar(CP_UTF8, NULL, szUtf8.c_str(), szUtf8.size(), NULL, 0);
		//malloc and fill the returned block
		wchar_t* szUnicode = new wchar_t[len + 1];
		MultiByteToWideChar(CP_UTF8, NULL, szUtf8.c_str(), szUtf8.size(), szUnicode, len);
		szUnicode[len] = 0;
		std::wstring rs = szUnicode;
		delete[] szUnicode;
		return rs;
	}

	static string Multi_To_UTF8(const std::string& multiText)
	{
		string utf8Text;
		// 把输入转换为Unicode
		int size = ::MultiByteToWideChar(CP_ACP,
			0,
			multiText.c_str(),
			-1,
			NULL,
			0);
		if (0 == size)
		{
			return "";
		}

		wchar_t* wszBuffer = new wchar_t[size + 1];
		::ZeroMemory(wszBuffer, (size + 1) * sizeof(wchar_t));

		if (0 == ::MultiByteToWideChar(CP_ACP,
			0,
			multiText.c_str(),
			-1,
			wszBuffer,
			size + 1))
		{
			delete[] wszBuffer;
			return "";
		}

		// Unicode->UTF8的转换
		size = ::WideCharToMultiByte(CP_UTF8,
			0,
			wszBuffer,
			-1,
			NULL,
			0,
			NULL,
			NULL);
		if (0 == size)
		{
			delete[] wszBuffer;
			return "";
		}

		char* szBuffer = new char[size + 1];
		::ZeroMemory(szBuffer, (size + 1) * sizeof(char));

		if (0 == ::WideCharToMultiByte(CP_UTF8,
			0,
			wszBuffer,
			-1,
			szBuffer,
			size + 1,
			NULL,
			NULL))
		{
			delete[] wszBuffer;
			delete[] szBuffer;
			return "";
		}

		utf8Text = szBuffer;
		delete[] wszBuffer;
		delete[] szBuffer;
		return utf8Text;
	}

	static unsigned char ToHex(unsigned char x)
	{
		return  x > 9 ? x + 55 : x + 48;
	}

	static unsigned char FromHex(unsigned char x)
	{
		unsigned char y;
		if (x >= 'A' && x <= 'Z') y = x - 'A' + 10;
		else if (x >= 'a' && x <= 'z') y = x - 'a' + 10;
		else if (x >= '0' && x <= '9') y = x - '0';
		else assert(0);
		return y;
	}

	static std::string UrlEncode(const std::string& str)
	{
		std::string strTemp = "";
		size_t length = str.length();
		for (size_t i = 0; i < length; i++) {
			if (isalnum((unsigned char)str[i]) ||
				(str[i] == '-') || (str[i] == '_') ||
				(str[i] == '.') || (str[i] == '/') ||
				(str[i] == '?') || (str[i] == ':') ||
				(str[i] == '=') || (str[i] == '&') ||
				(str[i] == '~')) {
				strTemp += str[i];
			}
			else if (str[i] == ' ') {
				strTemp += "+";
			}
			else
			{
				strTemp += '%';
				strTemp += ToHex((unsigned char)str[i] >> 4);
				strTemp += ToHex((unsigned char)str[i] % 16);
			}
		}
		return strTemp;
	}

	static std::string UrlDecode(const std::string& str)
	{
		std::string strTemp = "";
		size_t length = str.length();
		for (size_t i = 0; i < length; i++)
		{
			if (str[i] == '+') strTemp += ' ';
			else if (str[i] == '%')
			{
				assert(i + 2 < length);
				unsigned char high = FromHex((unsigned char)str[++i]);
				unsigned char low = FromHex((unsigned char)str[++i]);
				strTemp += high * 16 + low;
			}
			else strTemp += str[i];
		}
		return strTemp;
	}
};
