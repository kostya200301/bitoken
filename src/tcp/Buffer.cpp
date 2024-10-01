//
// Created by Константин Беляков on 07.09.2024.
//

#include "Buffer.h"

namespace tcp {

    void Buffer::finish_work() {
//        get_boost_buffer()->consume(buffer_->size());
        spdlog::trace("[TCP] Buffer: finish work id = {}", id_);
        on_finish_work_();
    }
}