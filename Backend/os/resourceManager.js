
function createResourceManager(initialResources){

  let resources={...initialResources};

  let maxResources={...initialResources};

  function allocateResource(resourceName,quantity){

    if(resources[resourceName]===undefined){

      return "Resource not found";

    }

    if(!Number.isInteger(quantity) || quantity<=0){

      return "Invalid quantity";

    }

    if(resources[resourceName]>=quantity){

      resources[resourceName]-=quantity;

      return "Resource allocated successfully";

    }

    return "Not enough resources available";

  }

  function releaseResource(resourceName,quantity){

    if(resources[resourceName]===undefined || !Number.isInteger(quantity) || quantity<=0){

      return "Invalid resource or quantity";

    }

    if(resources[resourceName]+quantity>maxResources[resourceName]){

      return "Cannot release more than maximum capacity";

    }

    resources[resourceName]+=quantity;

    return "Resource released successfully";

  }

  function getResources(){

    return {...resources};

  }

  return {
    allocateResource:allocateResource,
    releaseResource:releaseResource,
    getResources:getResources
  };

}

module.exports={
  createResourceManager:createResourceManager
};