/*
 *  Open/Close Shield
 *
 *  Author: Goldilocks, Austin, Patrick, and Richard
 *  Date: 2014-11-22
 *  Revision: 2014-11-22
 *  Capabilities:
 *   Switch
 *  Custom Commands
 *   open
 *   close
 */
 
 
metadata {
    definition (name: "Open/Close Shield", author: "Goldilocks, Austin, Patrick, and Richard") {
            capability "Switch"
            command "open"
            command "close"
            command "message"
    }
 
    tiles {

        standardTile("OpenClose", "device.switch", width: 2, height: 2, canChangeIcon: true, canChangeBackground: true) {
            state "open", label: '${name}', action: "close", icon: "st.switches.switch.on", backgroundColor: "#79b821"
            state "close", label: '${name}', action: "open", icon: "st.switches.switch.off", backgroundColor: "#ffffff"
        }
        
        main "OpenClose"
    }
    simulator {
        status "on":  "catchall: 0104 0000 01 01 0040 00 0A21 00 00 0000 0A 00 0A6F6E"
        status "off": "catchall: 0104 0000 01 01 0040 00 0A21 00 00 0000 0A 00 0A6F6666"
    
        // reply messages
        reply "raw 0x0 { 00 00 0a 0a 6f 6e }": "catchall: 0104 0000 01 01 0040 00 0A21 00 00 0000 0A 00 0A6F6E"
        reply "raw 0x0 { 00 00 0a 0a 6f 66 66 }": "catchall: 0104 0000 01 01 0040 00 0A21 00 00 0000 0A 00 0A6F6666"
    }
}
 

def on() {
    zigbee.smartShield(text: "on").format()
}
 
def off() {
    zigbee.smartShield(text: "off").format()
}
 
def open() {
    log.debug "Open Window!"
    zigbee.smartShield(text: "open").format()
}
 
def close() {
    log.debug "Close Window!"
    zigbee.smartShield(text: "close").format()
}

def message(float distance) {
    log.debug "Adjust Window"
    zigbee.smartShield(text: distance.toString()).format()
}
 
def parse(String description) {
    log.debug "Parsing '${description}'" 
}