let resources={
  ICU_BED:2,
  VENTILATOR:3,
  OXYGEN_CYLINDER:5
};
function allocateResource(resourceName,quantity){
  if(resources[resourceName]===undefined){
    return "Resource not found";
  }
  if(quantity<=0){
    return "Invalid quantity";
  }
  if(resources[resourceName]>=quantity){
    resource[resourceName]-=quantity;
    return "Resource allocated successfully";
  }
  return "Not enough resorces available";
}
function releaseResource(resourceName,quantity){
  if(resouces[resourceName]===undefined || quantity<=0){
    return "Invalid resources or quantity";
  }
  resources[resourceName]+=quantity;
  return "Resource released successfully";
}
function getResource(){
  return resources;
}
moduleexports={
  allocateResource:allocateResource,
  releaseResource:releaseResource,
  getResource:getResource
};