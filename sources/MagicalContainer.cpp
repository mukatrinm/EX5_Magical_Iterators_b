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
    if (ptr_magical_containter != other.ptr_magical_containter) {
        throw std::runtime_error("Comparing different conrainers.");
    }

    return ptr_magical_containter == other.ptr_magical_containter && _index == other._index;
}

bool MagicalContainer::BaseIterator::operator!=(const BaseIterator &other) const {
    return !(*this == other);
}

bool MagicalContainer::BaseIterator::operator>(const BaseIterator &other) const {
    return ptr_magical_containter == other.ptr_magical_containter && getIndex() > other.getIndex();
}

bool MagicalContainer::BaseIterator::operator<(const BaseIterator &other) const {
    return ptr_magical_containter == other.ptr_magical_containter && getIndex() < other.getIndex();
}

MagicalContainer::BaseIterator &MagicalContainer::BaseIterator::operator=(const BaseIterator &other) {
    if (ptr_magical_containter != other.ptr_magical_containter) {
        throw std::runtime_error("iterators have different conrainers.");
    }

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
    if (*this == end()) {
        throw std::runtime_error("out of range.");
    }
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
    if (*this == end()) {
        throw std::runtime_error("SideCrossIterator out of range.");
    }
    if (is_end_turn) {
        end_index_--;
    } else {
        setIndex(getIndex() + 1);
    }

    // move the index to out of range
    if (end_index_ < getIndex()) {
        setIndex(getMagicalContainer()->size());
    }

    is_end_turn = !is_end_turn;  // alternate the value

    return *this;
}

int MagicalContainer::SideCrossIterator::operator*() const {
    if (getMagicalContainer() == nullptr) {
        throw std::runtime_error("Container is null.");
    }

    auto ptr_magical_containter = getMagicalContainer();
    size_t container_size = ptr_magical_containter->_mystical_elements.size();

    if (getIndex() >= container_size || end_index_ < 0) {
        throw std::out_of_range("Index is out of range.");
    }

    if (is_end_turn) {
        return ptr_magical_containter->_mystical_elements[end_index_];
    }

    return ptr_magical_containter->_mystical_elements[getIndex()];
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() {
    return SideCrossIterator(*getMagicalContainer());
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() {
    SideCrossIterator iter(*getMagicalContainer());
    iter.setIndex(getMagicalContainer()->_mystical_elements.size());
    iter.end_index_ = 0;
    return iter;
}

/*****************
 * PrimeIterator *
 *****************/

MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &ptr_magical_containter, std::size_t index) : BaseIterator(&ptr_magical_containter, index),
                                                                                                              last_prime_index_{getMagicalContainer()->_mystical_elements.size()},
                                                                                                              first_time_{true} {
    // last_prime_index_ is the index of the last prime number in the container
    if (getMagicalContainer()->size() != 0) {
        last_prime_index_ = getMagicalContainer()->size() - 1;
        // last_prime_index_ should point to one past the last prime index
        while (last_prime_index_ > 0) {
            if (isPrime(getMagicalContainer()->_mystical_elements.at(last_prime_index_))) {
                break;
            }
            last_prime_index_--;
        }
    }

    // index_ is the index of the first prime number in the container
    while (getIndex() < getMagicalContainer()->size()) {
        if (isPrime(getMagicalContainer()->_mystical_elements.at(getIndex()))) {
            break;
        }
        setIndex(getIndex() + 1);
    }

    // std::cout << "first_prime_idx: " << first_prime_idx << std::endl;
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++() {
    if (*this == end()) {
        throw std::runtime_error("out of range");
    }

    if (getIndex() > last_prime_index_) {
        throw std::runtime_error("out of range");
    }

    if (getIndex() < getMagicalContainer()->size()) {
        setIndex(getIndex() + 1);
    }

    while (getIndex() < getMagicalContainer()->_mystical_elements.size() && !isPrime(getMagicalContainer()->_mystical_elements.at(getIndex()))) {
        setIndex(getIndex() + 1);
    }

    // std::cout << "getIndex(): " << getIndex() << std::endl;
    // std::cout << "last_prime_index_(): " << getIndex() << "\n--------------------" << std::endl;
    // check if it's the last prime
    // if (last_prime_index_ == 0) {
    //     setIndex(1);
    // }

    if (getIndex() > last_prime_index_) {
        // std::cout << "last_prime_index_: " << last_prime_index_ << std::endl;
        // std::cout << "if >=  last_prime_index_ reached" << std::endl;
        setIndex(last_prime_index_ + 1);
    }

    return *this;
}

int MagicalContainer::PrimeIterator::operator*() {
    if (getMagicalContainer() == nullptr) {
        throw std::runtime_error("Container is null.");
    }
    if (getMagicalContainer()->size() == 0) {
        throw std::runtime_error("Container is empty.");
    }

    if (first_time_) {
        first_time_ = false;
        while (getIndex() < getMagicalContainer()->size()) {
            if (isPrime(getMagicalContainer()->_mystical_elements.at(getIndex()))) {
                return getMagicalContainer()->_mystical_elements.at(getIndex());
            }
            setIndex(getIndex() + 1);
        }
    }
    return getMagicalContainer()->_mystical_elements.at(getIndex());
    // throw std::runtime_error("The container has no prime numberrrrr.");
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() {
    PrimeIterator iter(*getMagicalContainer());
    // size_t first_prime_idx = 0;
    // while (first_prime_idx < getMagicalContainer()->size()) {
    //     if (isPrime(iter.getMagicalContainer()->_mystical_elements.at(first_prime_idx))) {
    //         break;
    //     }
    //     first_prime_idx++;
    // }
    // if (first_prime_idx >= getMagicalContainer()->size()) {
    //     throw std::runtime_error("The container has no prime number.");
    // }

    // // std::cout << "first_prime_idx: " << first_prime_idx << std::endl;

    // iter.setIndex(first_prime_idx);
    return iter;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() {
    PrimeIterator iter(*getMagicalContainer());

    if (last_prime_index_ <= 0) {
        // no prime found
        iter.setIndex(0);
    } else {
        iter.setIndex(last_prime_index_ + 1);
    }

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
