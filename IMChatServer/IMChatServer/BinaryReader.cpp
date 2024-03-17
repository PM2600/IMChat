#include "BinaryReader.h"
namespace edoyun {
	template<>
	bool BinaryReader::ReadData(string& data) {
		const char* pcur = m_buffer.c_str() + m_index;
		int length = 0;
		size_t i = 0;
		for (; i < m_buffer.size() - m_index; i++) {
			length <<= 7;
			length |= pcur[i] & 0x7F;
			if ((pcur[i] & 0x80) == 0)break;
		}
		m_index += i + 1;
		data.assign(m_buffer.c_str() + m_index, length);
		m_index += length;
		return true;
	}
	template<>
	bool BinaryWriter::WriteData(const string& data) {
		string out;
		Compress(data.size(), out);
		m_buffer.append(out.c_str(), out.size());
		m_index += out.size();
		if (data.size() > 0) {
			m_buffer.append(data.c_str(), data.size());
			m_index += data.size();
		}
		return true;
	}
}