#pragma once

#include <memory>

namespace ecu
{

struct OutputChannelBase;

struct IEcu
{
    virtual std::shared_ptr<OutputChannelBase> FindChannel(const std::string& id) const = 0;
};

} // namespace ecu
