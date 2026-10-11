
function checkStarvation(processes,currentTime,maxWaitingTime){

  let starvedProcesses=[];

  for(let i=0;i<processes.length;i++){

    let waitingTime=currentTime-processes[i].arrivalTime;

    if(processes[i].state!="Completed" && processes[i].state!="COMPLETED" && waitingTime>=maxWaitingTime){

      starvedProcesses.push(processes[i]);

    }

  }

  return starvedProcesses;

}

module.exports={

  checkStarvation:checkStarvation

};