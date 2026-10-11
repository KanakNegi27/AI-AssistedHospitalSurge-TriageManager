
const { createProcess } = require("./os/process");
const { fcfsScheduling } = require("./os/fcfs");
const { sjfScheduling } = require("./os/sjf");
const { priorityScheduling } = require("./os/priority");
const { roundRobinScheduling } = require("./os/roundRobin");

function createTestProcesses(){

  return [
    createProcess("E1",0,5,2),
    createProcess("E2",1,3,1),
    createProcess("E3",2,2,3)
  ];

}

function displayResult(name,result){

  console.log("\n"+name);

  console.table(result.map(function(process){

    return {
      ID:process.id,
      AT:process.arrivalTime,
      BT:process.burstTime,
      Priority:process.priority,
      CT:process.completionTime,
      TAT:process.turnaroundTime,
      WT:process.waitingTime,
      State:process.state
    };

  }));

}

displayResult("FCFS",fcfsScheduling(createTestProcesses()));

displayResult("SJF",sjfScheduling(createTestProcesses()));

displayResult("Priority Scheduling",priorityScheduling(createTestProcesses()));

displayResult("Round Robin",roundRobinScheduling(createTestProcesses(),2));