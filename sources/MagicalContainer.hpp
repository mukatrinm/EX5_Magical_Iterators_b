#pragma once

#include <iostream>
#include <vector>

namespace ariel {
class MagicalContainer {
   private:
    std::vector<int> _mystical_elements;

   public:
    MagicalContainer() {}

    void addElement(int element);
    void removeElement(int element);

    size_t size() const;

    class BaseIterator {
       private:
        MagicalContainer *ptr_magical_containter = nullptr;
        size_t _index = 0;

       protected:
        MagicalContainer *getMagicalContainer() const { return ptr_magical_containter; }
        size_t getIndex() const { return _index; }
        void setIndex(size_t new_index) { _index = new_index; }

       public:
        BaseIterator(MagicalContainer *container, size_t index = 0) : ptr_magical_containter(container), _index(index){};
        BaseIterator(const BaseIterator &other)
            : ptr_magical_containter(other.ptr_magical_containter), _index(other._index) {}

        BaseIterator(BaseIterator &&other) = delete;
        BaseIterator &operator=(BaseIterator &&other) = delete;
        BaseIterator &operator=(const BaseIterator &other);

        virtual ~BaseIterator() = default;

        bool operator==(const BaseIterator &other) const;
        bool operator!=(const BaseIterator &other) const;
        bool operator<(const BaseIterator &other) const;
        bool operator>(const BaseIterator &other) const;
        int operator*() const;
    };

    class AscendingIterator : public BaseIterator {
       public:
        AscendingIterator(MagicalContainer &ptr_magical_containter, size_t index = 0) : BaseIterator(&ptr_magical_containter, index) {}
        AscendingIterator(const AscendingIterator &other) : BaseIterator(other) {}
        AscendingIterator(AscendingIterator &&other) = delete;
        AscendingIterator &operator=(AscendingIterator &&other) = delete;
        AscendingIterator &operator=(const AscendingIterator &other);
        ~AscendingIterator() override = default;

        AscendingIterator &operator++();

        AscendingIterator begin();
        AscendingIterator end();
    };

    class SideCrossIterator : public BaseIterator {
       public:
        SideCrossIterator(MagicalContainer &ptr_magical_containter, size_t index = 0) : BaseIterator(&ptr_magical_containter, index) {}
        SideCrossIterator(const SideCrossIterator &other) : BaseIterator(other) {}
        SideCrossIterator(SideCrossIterator &&other) = delete;
        SideCrossIterator &operator=(SideCrossIterator &&other) = delete;
        SideCrossIterator &operator=(const SideCrossIterator &other);
        ~SideCrossIterator() override = default;

        SideCrossIterator &operator++();

        SideCrossIterator begin();
        SideCrossIterator end();
    };

    class PrimeIterator : public BaseIterator {
       public:
        PrimeIterator(MagicalContainer &ptr_magical_containter, size_t index = 0) : BaseIterator(&ptr_magical_containter, index) {}
        PrimeIterator(const PrimeIterator &other) : BaseIterator(other) {}
        PrimeIterator(PrimeIterator &&other) = delete;
        PrimeIterator &operator=(PrimeIterator &&other) = delete;
        PrimeIterator &operator=(const PrimeIterator &other);
        ~PrimeIterator() override = default;

        PrimeIterator &operator++();

        PrimeIterator begin();
        PrimeIterator end();
    };
};
}  // namespace ariel