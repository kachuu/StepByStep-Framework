# Step By Step Framework  
Object-oriented design in a Qt environment, step-by-step framework.  
  
Every event is composed of many independent sub-events, which can be grouped through clustering methods to form slightly larger or slightly smaller events. Software design can also apply this concept by clustering the functions performed by multiple lines of code into a slightly larger whole. In higher-level design concepts, they are objects with specific lifecycles.  
  
The design of a "step-by-step framework" is based on a timeline, dividing the entire event into multiple independent event units. These event units can also be further subdivided until they reach an appropriate level of complexity. These event units benefit from the concept of object lifecycle, serving as self-contained entities that can be easily replaced even if there are changes in software functionality.  
  
### How framework Work  
The entire "step-by-step framework" benefits from Qt's signal/slot feature, making it easy to connect with passive functionalities.  
  
We abstract the steps into an object body, which has multiple start points (active start points via the *exe()*, passive start points via the *slot()*), and multiple end points (functions returning in sequential calls, *signal()* triggered by events).  
  
The execution status of steps can also be categorized as: continuing execution(*NEXT*), waiting(*WAIT*), or execution failure(*END*). These statuses will guide subsequent processing flows and can be considered as conditional branches.  

Based on the complexity of steps, various smaller independent steps can be further subdivided. These smaller, independent steps collectively form a *StepList*. The execution of steps follows a linear order, with jumps occurring only when encountering conditional selections. The sequential list and conditional jumps provide flexibility to the framework.  
  
For example, StepHandle2 needs to be executed three times on a timed schedule. To simplify, its content can be further subdivided into three individual steps.  
![image](https://github.com/kachuu/StepFramework/blob/main/stepFramework.png)  
  
## Example  
### Create a simple step object  
Create a class that inherits from *StepInterface*. Override *exe()* and *slot()* based on the business requirements of the steps. Don't forget to add the *Q_OBJECT* macro.  
```bash  
class Step : public StepInterface {
    Q_OBJECT

    RESULT exe() {
        //to do something
    }

    void slt_successful(StepInterface *p) {
        //to do something
    }
};
```  
  
### Establish a set of steps according to business requirements  
Create a container for a collection of steps that controls the execution sequence of the step queue (sequential execution or conditional jumps). It's essentially a slightly more complex *simple step object*  
```bash  
StepPtr Handle(StepPtr(new Handle()));
```  
  
The independent steps related to the business are added to the steps collection container, ultimately achieving the business requirements.  
```bash  
Handle->m_stepList.append(StepPtr(new Step()));
```  
  
Establish an association between steps and containers. Steps are independent, they don't concern themselves with the states of other steps or containers, aiming for low coupling. Containers are used to control the execution sequence of steps and must couple with each step. These processes benefit from Qt's signal/slot mechanism.  
```bash  
connect(&*Handle->m_stepList[i], SIGNAL(sig_startup(StepInterface*)), &*Handle, SLOT(slt_startup(StepInterface*)));
```  
  
### Startup  
The usual way to start executing is by invoking the entry point of the container.  
```bash  
Handle->exe();
```  
  
