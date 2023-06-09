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
        void setMagicalContainer(MagicalContainer *new_ptr_magical_containter) { ptr_magical_containter = new_ptr_magical_containter; }
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
        virtual BaseIterator &operator++() = 0;
        int operator*() const;
    };

    class AscendingIterator : public BaseIterator {
       public:
        AscendingIterator(MagicalContainer &ptr_magical_containter, size_t index = 0) : BaseIterator(&ptr_magical_containter, index) {}
        AscendingIterator(const AscendingIterator &other) : BaseIterator(other) {}
        // AscendingIterator(AscendingIterator &&other) noexcept;
        // AscendingIterator &operator=(AscendingIterator &&other);
        // AscendingIterator &operator=(const AscendingIterator &other);
        ~AscendingIterator() override = default;

        AscendingIterator &operator++() override;

        AscendingIterator begin();
        AscendingIterator end();
    };

    class SideCrossIterator : public BaseIterator {
       public:
        SideCrossIterator(MagicalContainer &ptr_magical_containter, size_t index = 0) : BaseIterator(&ptr_magical_containter, index) {}
        SideCrossIterator(const SideCrossIterator &other) : BaseIterator(other) {}
        // SideCrossIterator(SideCrossIterator &&other);
        // SideCrossIterator &operator=(SideCrossIterator &&other);
        // SideCrossIterator &operator=(const SideCrossIterator &other);
        ~SideCrossIterator() override = default;

        SideCrossIterator &operator++() override;

        SideCrossIterator begin();
        SideCrossIterator end();
    };

    class PrimeIterator : public BaseIterator {
       public:
        PrimeIterator(MagicalContainer &ptr_magical_containter, size_t index = 0) : BaseIterator(&ptr_magical_containter, index) {}
        PrimeIterator(const PrimeIterator &other) : BaseIterator(other) {}
        // PrimeIterator(PrimeIterator &&other);
        // PrimeIterator &operator=(PrimeIterator &&other);
        // PrimeIterator &operator=(const PrimeIterator &other);
        ~PrimeIterator() override = default;

        PrimeIterator &operator++() override;

        PrimeIterator begin();
        PrimeIterator end();
    };
};
}  // namespace ariel