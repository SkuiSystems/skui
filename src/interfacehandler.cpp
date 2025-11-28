#include "interfacehandler.h"

Q_DECLARE_LOGGING_CATEGORY(interfacehandler)
Q_LOGGING_CATEGORY(interfacehandler, "INTERFACE_HANDLER")

InterfaceHandler::InterfaceHandler() {}

InterfaceHandler &InterfaceHandler::getInstance()
{
    static InterfaceHandler handler;
    return handler;
}

void InterfaceHandler::registerInterface(InterfaceInfo present_interface,
                                         InterfaceDirection direction)
{
    QList<InterfaceInfo> *interfaces;
    QString direction_string;
    if (direction == InterfaceDirection::Input) {
        interfaces = &m_input_interfaces;
        direction_string = "Input";
    } else { // direction == InterfaceDirection::Output
        interfaces = &m_output_interfaces;
        direction_string = "Output";
    }
    interfaces->append(present_interface);

    qInfo(interfacehandler) << QString("Registered Interface for nid=%1 as %2 and type '%3'")
                                   .arg(present_interface.nid)
                                   .arg(direction_string)
                                   .arg(present_interface.data.typeName());
}
