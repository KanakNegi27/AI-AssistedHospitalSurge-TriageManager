function priorityScheduling(processes){
  let comp=[];
  let rem=processes.slice();
  let time=0;
  while(rem.length>0){
    let highest=-1;
    for(let i=0;i<rem.length;i++){
      if(rem[i].arrivalTime<=time){
        if(highest==-1 || rem[i].priority>rem[highest].priority){
          highest=i;
        }
      }
    }
    if(highest==-1){
      time++;
      continue;
    }
    let process=rem[highest];
    process.state="Running";
    time+=process.burstTime;
    process.state="Completed";
    process.completionTime=time;
    process.turnaroundTime=process.completionTime-process.arrivalTime;
    process.waitingTime=process.turnaroundTime-process.burstTime;
    comp.push(process);
    rem.splice(highest,1);
  }
  return comp;
}
module.exports={
  priorityScheduling:priorityScheduling
};