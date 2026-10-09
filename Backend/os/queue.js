let readyQueue=[];
function addProcess(process){
  readyQueue.push(process);
}
function getQueue(){
  return readyQueue;
}
function removeProcess(){
  return readyQueue.shift();
}
module.exports={
  addProcess:addProcess,
  getQueue:getQueue,
  removeProcess:removeProcess
};