let waitingCase=[];
function addWaitingCase(emergencyCase){
  emergencyCase.state="Waiting";
  waitingCase.push(emergencyCase);
  return "Case added to resouce waiting queue";
}
function getWaitingCases() {
return waitingCases;
}

function removeWaitingCase() {

if (waitingCases.length === 0) {
    return null;
}

return waitingCases.shift();

}

module.exports = {
addWaitingCase: addWaitingCase,
getWaitingCases: getWaitingCases,
removeWaitingCase: removeWaitingCase
};