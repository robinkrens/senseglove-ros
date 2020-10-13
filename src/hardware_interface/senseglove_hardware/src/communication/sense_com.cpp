//Copyright 2020 Senseglove.
#include <memory>
#include "senseglove_hardware/communication/sense_com.h"
#include <string>
#include <thread>
#include <utility>
#include <vector>
#include <ros/ros.h>
#include "SGConnect.h"

namespace senseglove
{
    Sensecom::Sensecom(int max_slave_index, int cycle_time) : is_operational_(false),
    max_slave_index_(max_slave_index), cycle_time_ms_(cycle_time)
    {
    }

    Sensecom::~Sensecom()
    {
        this->stop();
    }

    bool Sensecom::isOperational() const
    {
        return this->is_operational_;
    }

    int Sensecom::getCycleTime() const
    {
        return this->cycle_time_ms_;
    }

    int Sensecom::start()
    {
        if (!SGConnect::ScanningActive())
        {
            return SGConnect::Init();
        }
        else
        {
            ROS_WARN("SGConnect Scanning is already Active! Will not instantiate a new SGConnect object");
        }
        return 0;
    }

    void Sensecom::stop()
    {
        if (this->is_operational_)
        {
            ROS_INFO("Stopping communication with Senseglove device");
            this->is_operational_ = false;
            int result = SGConnect::Dispose();
            this->communication_thread_.join();
            ROS_INFO("SGConnect Dispose returned with result: %d", result);
        }
    }
}