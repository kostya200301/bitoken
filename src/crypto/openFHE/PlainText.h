//
// Created by Константин Беляков on 30.11.2024.
//

#ifndef BITOCEN_PLAINTEXT_H
#define BITOCEN_PLAINTEXT_H

#include "openfhe.h"
#include "crypto/IPlainText.h"
#include <vector>

namespace crypto {

    class PlainText;
    using PlainTextPtr = std::shared_ptr<PlainText>;

    class PlainText : public IPlainText {
    public:
        PlainText(std::shared_ptr<lbcrypto::PlaintextImpl> const& pt);

        ~PlainText() override;

        [[nodiscard]] const std::vector<int64_t> get_int64_vec() const override;

        friend class CryptoContext;

    private:
        std::shared_ptr<lbcrypto::PlaintextImpl> pt_;
    };

}


#endif //BITOCEN_PLAINTEXT_H
