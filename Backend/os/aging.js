function applyAging(processes,currentTime,waitingLimit){
  for(let i=0;i<processes.length;i++){
    if(processes[i].state=='Ready'){
      let waitingTime=currentTime-processes[i].arrivalTime;
      if(waitingTime>=waitingLimit){
        if(processes[i].priority>1){
          processes[i].priority--;
        }
      }
    }
  }
  return processes;
}
module.exports={
  applyAging:applyAging
};