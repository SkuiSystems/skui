#ifndef INTERFACEHANDLER_H
#define INTERFACEHANDLER_H

#include <QList>
#include <QLoggingCategory>
#include <QString>
#include <QVariant>

#define OUTPUT_INTERFACE(nid, variable) \
    InterfaceHandler::getInstance().registerInterface({nid, QVariant::fromValue(variable)}, \
                                                      InterfaceDirection::Output);
#define INPUT_INTERFACE(nid, variable) \
    InterfaceHandler::getInstance().registerInterface({nid, QVariant::fromValue(variable)}, \
                                                      InterfaceDirection::Input);

enum class InterfaceDirection { Input, Output };

struct InterfaceInfo
{
    int nid;
    QVariant data;
};

class InterfaceHandler
{
public:
    InterfaceHandler();

    static InterfaceHandler &getInstance();

    void registerInterface(InterfaceInfo, InterfaceDirection);
    void registerConnection();
    void deregisterConnection();

private:
    InterfaceHandler(const InterfaceHandler &) = delete;
    InterfaceHandler &operator=(const InterfaceHandler &) = delete;
    InterfaceHandler(InterfaceHandler &&) = delete;
    InterfaceHandler &operator=(InterfaceHandler &&) = delete;

    QList<InterfaceInfo> m_output_interfaces;
    QList<InterfaceInfo> m_input_interfaces;
};

#endif // INTERFACEHANDLER_H
