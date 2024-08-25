#pragma once

#include <boost/signals2.hpp>

namespace bs {
    using namespace boost::signals2;
}

template<typename FuncT>
using signal_type = boost::signals2::signal<FuncT>;

typedef bs::scoped_connection scoped_connection;

typedef std::shared_ptr<scoped_connection> scoped_connection_ptr;

template<typename Signal, typename Slot>
scoped_connection_ptr connect_slot(Signal& signal, Slot&& slot) {
    return std::make_shared<scoped_connection>(signal.connect(slot));
};


#define INLINE_SIGNAL(NAME, SIGNATURE)                                                                                 \
    typedef signal_type<SIGNATURE> NAME##_signal;                                                                      \
    scoped_connection_ptr on_##NAME##_slot(NAME##_signal::slot_type slot) { return connect_slot(on_##NAME##_, slot); } \
                                                                                                                       \
protected:                                                                                                             \
    NAME##_signal on_##NAME##_;