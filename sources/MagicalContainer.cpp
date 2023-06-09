#include "MagicalContainer.hpp"

#include <algorithm>
#include <cmath>
#include <vector>

using namespace ariel;

/********************
 * MagicalContainer *
 *********************/

void MagicalContainer::addElement(int element) {
    _mystical_elements.push_back(element);
    std::sort(_mystical_elements.begin(), _mystical_elements.end());
}

void MagicalContainer::removeElement(int element) {
    auto iter = std::find(_mystical_elements.begin(), _mystical_elements.end(), element);

    if (iter == _mystical_elements.end()) {
        throw std::runtime_error("Element doesn't exist.");
    }

    _mystical_elements.erase(iter);
}

size_t MagicalContainer::size() const {
    return _mystical_elements.size();
}

/******************
 * BaseIterator *
 *******************/

bool MagicalContainer::BaseIterator::operator==(const BaseIterator &other) const {
    return ptr_magical_containter == other.ptr_magical_containter && _index == other._index;
}

bool MagicalContainer::BaseIterator::operator!=(const BaseIterator &other) const {
    return !(*this == other);
}

bool MagicalContainer::BaseIterator::operator>(const BaseIterator &other) const {
    return ptr_magical_containter->_mystical_elements[_index] > other.ptr_magical_containter->_mystical_elements[_index];
}

bool MagicalContainer::BaseIterator::operator<(const BaseIterator &other) const {
    return ptr_magical_containter->_mystical_elements[_index] < other.ptr_magical_containter->_mystical_elements[_index];
}

MagicalContainer::BaseIterator &MagicalContainer::BaseIterator::operator=(const BaseIterator &other) {
    if (this != &other) {
        ptr_magical_containter = other.ptr_magical_containter;
        _index = other._index;
    }
    return *this;
}

int MagicalContainer::BaseIterator::operator*() const {
    if (ptr_magical_containter == nullptr) {
        throw std::runtime_error("Container is null.");
    }

    if (_index >= ptr_magical_containter->_mystical_elements.size()) {
        throw std::out_of_range("Index is out of range.");
    }

    return ptr_magical_containter->_mystical_elements[_index];
}

/*********************
 * AscendingIterator *
 **********************/

// MagicalContainer::AscendingIterator::AscendingIterator(AscendingIterator &&other)
//     : BaseIterator(other.getMagicalContainer(), other.getIndex()) {
// }

// MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(AscendingIterator &&other) {
//     if (this != &other) {
//         setMagicalContainer(other.getMagicalContainer());
//         setIndex(other.getIndex());
//         // other.ptr_magical_containter = nullptr;
//         // other._index = 0;
//     }
//     return *this;
// }

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++() {
    setIndex(getIndex() + 1);
    return *this;
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() {
    return AscendingIterator(*getMagicalContainer());
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() {
    AscendingIterator iter(*getMagicalContainer());
    iter.setIndex(getMagicalContainer()->_mystical_elements.size());
    return iter;
}

/*********************
 * SideCrossIterator *
 *********************/

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++() {
    setIndex(getIndex() + 1);
    return *this;
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() {
    return SideCrossIterator(*getMagicalContainer());
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() {
    SideCrossIterator iter(*getMagicalContainer());
    iter.setIndex(getMagicalContainer()->_mystical_elements.size());
    return iter;
}

/*****************
 * PrimeIterator *
 *****************/

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++() {
    if (*this == end()) {
        throw std::runtime_error("out of range");
    }
    setIndex(getIndex() + 1);
    while (getIndex() < getMagicalContainer()->size() && !isPrime(getMagicalContainer()->_mystical_elements.at(getIndex()))) {
        setIndex(getIndex() + 1);
    }
    return *this;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() {
    return PrimeIterator(*getMagicalContainer());
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() {
    PrimeIterator iter(*getMagicalContainer());
    iter.setIndex(getMagicalContainer()->_mystical_elements.size());
    return iter;
}

bool MagicalContainer::PrimeIterator::isPrime(int num) const {
    if (num <= 1) {
        return false;
    }

    for (int i = 2; i <= static_cast<int>(std::sqrt(num)); ++i) {
        if (num % i == 0) {
            return false;
        }
    }

    return true;
}
