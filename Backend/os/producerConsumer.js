let buffer=[];
let bufferSize=5;
function produceCase(emergencyCase){
  if (buffer.length >= bufferSize) { return "Queue is full";
}
buffer.push(emergencyCase);
return "Emergency case addded to queue";
}
function consumeCase() {

if (buffer.length === 0) {
    return "Queue is empty";
}

return buffer.shift();

}

function getBuffer() {
return buffer;
}

module.exports = {
produceCase: produceCase,
consumeCase: consumeCase,
getBuffer: getBuffer
};