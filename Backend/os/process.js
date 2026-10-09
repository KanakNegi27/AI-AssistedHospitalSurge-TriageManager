function createProcess(id,arrivalTime,burstTime,priority){
  return{
    id:id,
    arrivalTime:arrivalTime,
    burstTime:burstTime,
    priority:priority,
    remainingTime:burstTime,
    state:"NEW"
  };
}
module.exports={
  createProcess:createProcess
};