function fcfsScheduling(processes){
  let comp=[];
  let rem=processes.slice();
  let time=0;
  while(rem.length>0){
    let first=-1;
    for(let i=0;i<rem.length;i++){
      if(rem[i].arrivalTime<=time){
        if(first==-1 || rem[i].arrivalTime<rem[first].arrivalTime){
          first=i;
        }
      }
    }
    if(first==-1){
      time++;
      continue;
    }
    let process=rem[first];
    process.state="Running";
    time+=process.burstTime;
    process.state="Completed";
    process.completionTime=time;
    process.turnaroundTime=process.completionTime-process.arrivalTime;
    process.waitingTime=process.turnaroundTime-process.burstTime;
    comp.push(process);
    rem.splice(first,1);
  }
  return comp;
}
module.exports={
  fcfsScheduling:fcfsScheduling
};