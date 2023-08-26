#include "RandomFile.hpp"

auto RandomFile::at(const RandomFile::key_type &key) -> RandomFile::data_type {
    Record record;
    record.m_data.first = key;
    record.m_data.second = this->m_index[key];
    return record;
}

auto RandomFile::insert(const RandomFile::data_type &data) -> bool {
    if (this->m_index.find(data.m_data.first) != this->m_index.end()) {
        this->m_index[data.m_data.first] = data.m_data.second;
        return true;
    }
    return false;
}
