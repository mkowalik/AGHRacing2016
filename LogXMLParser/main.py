import xml.dom.minidom

dom = xml.dom.minidom.parse("D:\\Dropbox\\AGH Racing\\version1_137.xml")

variables = dom.getElementsByTagName("variables")[0]
symbols = variables.getElementsByTagName("symbol")

for symbol in symbols:
    if symbol.hasAttribute("channel"):

        name = symbol.getAttribute('name').upper()
        channel = symbol.getAttribute('channel')
        divider = symbol.getAttribute('divider')
        unit = symbol.getAttribute('unit')
        if symbol.hasAttribute('gaugeDiv'):
            gaugeDiv = symbol.getAttribute('gaugeDiv')
        else:
            gaugeDiv = '1'
        gaugeMin = symbol.getAttribute('gaugeMin')
        gaugeMax = symbol.getAttribute('gaugeMax')
        userName = symbol.getAttribute('userName')

        print "Data_divider[ECU_" + name + "]" + "= " + divider + ";"
        print "Data_gaugeDivider[ECU_" + name + "]" + "= " + gaugeDiv + ";"
        print "Data_gaugeMinValue[ECU_" + name + "]" + "= " + gaugeMin + ";"
        print "Data_gaugeMaxValue[ECU_" + name + "]" + "= " + gaugeMax + ";"
        print "Data_unitString[ECU_" + name + "]" + "= \"" + unit + "\";"
        print "Data_fullName[ECU_" + name + "]" + "= \"" + userName + "\";"

        alarmCond = symbol.getAttribute('alarmCond')
        if alarmCond=='lt':
            alarm = symbol.getAttribute('alarm')
            print "Data_lowAlert[ECU_" + name + "]" + "= " + alarm + ";"
            print "Data_AlertMode[ECU_" + name + "]" + "= DATA_ONLY_LOW_VALUE_ALERT;"
        elif alarmCond=='gt':
            alarm = symbol.getAttribute('alarm')
            print "Data_highAlert[ECU_" + name + "]" + "= " + alarm + ";"
            print "Data_AlertMode[ECU_" + name + "]" + "= DATA_ONLY_HIGH_VALUE_ALERT;"

        print