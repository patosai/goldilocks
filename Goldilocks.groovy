/**
 *  Goldilocks
 *
 *  Copyright 2014 Goldilocks, Austin, Patrick, and Richard
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
 *  in compliance with the License. You may obtain a copy of the License at:
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software distributed under the License is distributed
 *  on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License
 *  for the specific language governing permissions and limitations under the License.
 *
 */
import groovy.sql.Sql
 
definition(
    name: "Goldilocks",
    namespace: "",
    author: "Goldilocks, Austin, Patrick, and Richard",
    description: "Modulate room temperature with nature's help!",
    category: "Convenience",
    iconUrl: "https://s3.amazonaws.com/smartapp-icons/Convenience/Cat-Convenience.png",
    iconX2Url: "https://s3.amazonaws.com/smartapp-icons/Convenience/Cat-Convenience@2x.png",
    iconX3Url: "https://s3.amazonaws.com/smartapp-icons/Convenience/Cat-Convenience@2x.png")


preferences {
	section("Goldilocks Device Selection") {
		input "temperatureSensor", "capability.temperatureMeasurement", title: "Temperature Probe"
        /// prescense sensor
        input "windowController", "capability.switch", title: "Window Controller"
	}
    section("Preferences") {
    	input "targetTemperature", "number", title: "Target Temperature"
        input "temperatureTolerance", "number", title: "Temperature Tolerance"
    }
}

def installed() {
	log.debug "Installed with settings: ${settings}"
	initialize()
}

def updated() {
	log.debug "Updated with settings: ${settings}"
	
	unsubscribe()
	initialize()
}

def initialize() {
    subscribe(temperatureSensor, "temperature", temperatureHandler)
    state.currentPosition = 0
    state.minPosition = 0
    state.maxPosition = 20
    state.moveLength = 0
}

// TODO: implement event handlers
def temperatureHandler(evt) {
    
    //new temperature reported
    log.debug "Updated Temperature"
	if(evt.doubleValue > (targetTemperature + temperatureTolerance)) {
    	log.debug "Opening window"
        if(state.moveLength < 0)
        	state.moveLength = state.moveLength * (targetTemperature - evt.doubleValue)/(targetTemperature)
        else if(state.moveLength > 0)
        	state.moveLength = state.moveLength * ((evt.doubleValue - targetTemperature)/(targetTemperature) + 1)
        else if(state.moveLength == 0)
        	state.moveLength = 1
        //check to make sure the window won't move past maxPosition
        if(state.moveLength + state.currentPosition > state.maxPosition)
        	state.moveLength = state.maxPosition - state.currentPosition
        state.currentPosition = state.currentPosition + state.moveLength
        log.debug state.moveLength.toString()
        //windowController.test()
      
        windowController.message(state.moveLength.toString())
        //Too hot, opening window
        
        //sendSQL(state.moveLength);

    }
    if(evt.doubleValue < (targetTemperature - temperatureTolerance)) {
    	log.debug "Closing window"
        if(state.moveLength > 0)
        	state.moveLength = state.moveLength * (evt.doubleValue - targetTemperature)/(targetTemperature)
        else if (state.moveLength < 0)
        	state.moveLength = state.moveLength * ((targetTemperature - evt.doubleValue)/(targetTemperature) + 1)
        else if(state.moveLength == 0)
        	state.moveLength = -1
        //check to make sure the window won't move past minPosition
        if(state.moveLength + state.currentPosition < state.minPosition)
        	state.moveLength = state.minPosition - state.currentPosition
        state.currentPosition = state.currentPosition + state.moveLength
        log.debug state.moveLength.toString()
        windowController.message(state.moveLength.toString())
        //Too cold, closing window
        
        //sendSQL(state.moveLength);

    }
	if(evt.doubleValue <= targetTemperature + temperatureTolerance && evt.doubleValue >= targetTemperature - temperatureTolerance)
    {
    	state.moveLength = 0
        log.debug state.moveLength.toString()
        windowController.message(state.moveLength.toString())
    }
}


def sendSQL(double distance) {
 	def sql = Sql.newInstance('jdbc:mysql://aiquvf0orh.database.windows.net:1433/data', 'patosai', '1Q!12345', 'org.hsqldb.jdbc.JDBCDriver')  
   	sql.execute "insert into data (id, widthOpen, temp, ambientTemp) values (1, $distance, 1,1)"

}

