
let waitingCases=[];

function addWaitingCase(emergencyCase){

  if(!emergencyCase){

    return "Invalid emergency case";

  }

  emergencyCase.state="WAITING";

  waitingCases.push(emergencyCase);

  return "Case added to resource waiting queue";

}

function getWaitingCases(){

  return [...waitingCases];

}

function removeWaitingCase(){

  if(waitingCases.length===0){

    return null;

  }

  return waitingCases.shift();

}

module.exports={

  addWaitingCase:addWaitingCase,

  getWaitingCases:getWaitingCases,

  removeWaitingCase:removeWaitingCase

};