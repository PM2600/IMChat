#pragma once
#include <iostream>
#include <string.h>
#include <string>


using namespace std;

namespace edoyun {

	class BinaryReader
	{
	public:
		static void dump(const string& buf) {
			dump(buf.c_str(), buf.size());
		}
		static void dump(const char* buf, size_t size) {
			for (size_t i = 0; i < size; i++) {
				if (i != 0 && ((i % 16) == 0))printf("\r\n");
				printf("%02X ", (unsigned)(buf[i]) & 0xFF);
			}
			printf("\r\n");
		}
	public:
		BinaryReader() { m_index = 0; }
		BinaryReader(const BinaryReader& reader) {
			m_buffer = reader.m_buffer;
			m_index = reader.m_index;
		}
		BinaryReader(const string& buffer) {
			m_index = 0;
			m_buffer = buffer;
		}
		~BinaryReader() = default;
		BinaryReader& operator=(const BinaryReader& reader) {
			if (this != &reader) {
				m_buffer = reader.m_buffer;
				m_index = reader.m_index;
			}
			return *this;
		}
		void UpdateBuffer(const string& buffer) {
			m_buffer = buffer;
			m_index = 0;
		}
		void Reset() { m_index = 0; }
		size_t Size() { return m_buffer.size(); }
		bool ReadInt32(int32_t& data) {
			if (m_index + sizeof(int32_t) > m_buffer.size())return false;
			memcpy(&data, m_buffer.c_str() + m_index, sizeof(int32_t));
			m_index += sizeof(int32_t);
			return true;
		}
		template<class T>
		bool ReadData(T& data) {
			if (m_index + sizeof(T) > m_buffer.size())return false;
			char* pData = (char*)&data;
			for (size_t i = 0; i < sizeof(T); i++)
			{
				pData[i] = *(m_buffer.c_str() + m_index + sizeof(T) - (i + 1));
			}
			m_index += sizeof(T);
			return true;
		}
	private:
		string m_buffer;
		uint32_t m_index;
	};

	template<>
	bool BinaryReader::ReadData(string& data);

	class BinaryWriter {
	public:
		BinaryWriter() :m_index(0) {}
		~BinaryWriter() {}
		template<class T>
		bool WriteData(const T& data) {
			m_buffer.resize(m_index + sizeof(T));
			memcpy((char*)m_buffer.c_str() + m_index, &data, sizeof(data));
			m_index += sizeof(T);
			return true;
		}
		uint32_t Size() { return m_index; }
		string toString()const { return m_buffer; }
		void Clear() {
			m_index = 0;
			m_buffer.clear();
		}
	protected:
		void Compress(size_t len, string& out) {
			char c = 0;
			if (len < 128) {
				c = (char)len & 0x7F;
				out += c;
				return;
			}
			//假定这个长度不会太长,百兆以内
			//输出的时候不会超过5个字节,32个bit能够表达
			for (int i = 4; i >= 0; i--) {
				c = (len >> (7 * i)) & 0x7F;
				//目前还没有发现有效数据，都是零
				if (c == 0 && out.size() == 0)
					continue;
				if (i > 0)//说明不是最后7位
					c |= 0x80;
				out += c;
			}
		}
	private:
		string m_buffer;
		uint32_t m_index;
	};
	template<>
	bool BinaryWriter::WriteData(const string& data);
}