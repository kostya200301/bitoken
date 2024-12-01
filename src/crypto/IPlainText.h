//
// Created by Константин Беляков on 30.11.2024.
//

#ifndef BITOCEN_IPLAINTEXT_H
#define BITOCEN_IPLAINTEXT_H

#include <memory>
#include <vector>


namespace crypto {

    class IPlainText;
    using IPlainTextPtr = std::shared_ptr<IPlainText>;

    class IPlainText {
    public:

        virtual ~IPlainText() = default;

        virtual const std::vector<int64_t> get_int64_vec() const = 0;

        friend std::ostream& operator<<(std::ostream& os, const IPlainText& keyPair) {
            auto vec = keyPair.get_int64_vec();
            os << "{";
            for (int i = 0; i < vec.size() - 1; i++) {
                os << vec[i] << ", ";
            }
            if (!vec.empty())
                os << vec[vec.size() - 1] << "}";
            return os;
        }

    };

}



#endif //BITOCEN_IPLAINTEXT_H
