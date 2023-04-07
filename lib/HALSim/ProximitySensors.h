/* MIT License
 *
 * Copyright (c) 2023 Andreas Merkle <web@blue-andi.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*******************************************************************************
    DESCRIPTION
*******************************************************************************/
/**
 * @brief  Proximity sensors realization
 * @author Andreas Merkle <web@blue-andi.de>
 *
 * @addtogroup HALInterfaces
 *
 * @{
 */
#ifndef PROXIMITYSENSORS_H
#define PROXIMITYSENSORS_H

/******************************************************************************
 * Compile Switches
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "IProximitySensors.h"
#include "SimTime.h"

#include <webots/Emitter.hpp>
#include <webots/DistanceSensor.hpp>

/******************************************************************************
 * Macros
 *****************************************************************************/

/******************************************************************************
 * Types and Classes
 *****************************************************************************/

/** The proximity sensors realization for the simulation. */
class ProximitySensors : public IProximitySensors
{
public:
    /**
     * Constructs the interface.
     */
    ProximitySensors(const SimTime& simTime, webots::DistanceSensor* frontSensor) :
        IProximitySensors(),
        m_frontSensor{frontSensor},
        m_sensorValueU8(0U)
    {
        if (nullptr != m_frontSensor)
        {
            m_frontSensor->enable(simTime.getTimeStep());
        }
    }

    /**
     * Destroys the interface.
     */
    virtual ~ProximitySensors()
    {
    }

    /**
     * Initialize only the front proximity sensor.
     */
    void initFrontSensor() final
    {
        /* Nothing to do. */
    }

    /**
     * Returns the number of sensors.
     *
     * @return Number of sensors
     */
    uint8_t getNumSensors() const final
    {
        return 1;
    }

    /**
     * Emits IR pulses and gets readings from the sensors.
     */
    void read() final
    {
        if (nullptr != m_frontSensor)
        {
            m_sensorValueU8 = static_cast<uint8_t>(m_frontSensor->getValue());
        }
    }

    /**
     * Returns the number of brightness levels for the left LEDs that
     * activated the front proximity sensor.
     *
     * @return Number of brightness levels
     */
    uint8_t countsFrontWithLeftLeds() const final
    {
        return m_sensorValueU8;
    }

    /**
     * Returns the number of brightness levels for the right LEDs that
     * activated the front proximity sensor.
     *
     * @return Number of brightness levels
     */
    uint8_t countsFrontWithRightLeds() const final
    {
        return m_sensorValueU8;
    }

protected:
private:
    /**
     * Max. value of a single proximity sensor in digits.
     * It depends on the Zumo32U4ProximitySensors implementation,
     * specifically the number of brightness levels.
     */
    static const int16_t SENSOR_MAX_VALUE = 6;

    webots::DistanceSensor* m_frontSensor;   /**< The frontal proximity sensor*/
    uint8_t                 m_sensorValueU8; /**< The last value read of the sensor as unsigned 8-bit values. */

    /* Default constructor not allowed. */
    ProximitySensors();
};

/******************************************************************************
 * Functions
 *****************************************************************************/

#endif /* PROXIMITYSENSORS_H */