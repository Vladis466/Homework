/*jslint browser:true, devel:true, white:true, vars:true */
/*global $:false, intel:false */
/*jshint browser:true */
/*jslint smarttabs:true */
/*global $ */(function()
{
 "use strict";
 /*
   hook up event handlers 
 */
	
 var Uname = "";
 var userLocation;
 function register_event_handlers()
 {
 //Global username variable is used throughout the project

 
      
        /* button  Login */
    $(document).on("click", ".uib_w_76", function(evt)
    {
        /* your code goes here */ 
		Uname = document.getElementById("nameInput").value; 
		var Upass = document.getElementById("passInput").value;
		if (Uname === "" || Upass === "")
		{
			document.getElementById("authResponse").innerHTML = "Please fill out the fields";
		} else
		{
			intel.xdk.device.getRemoteData("http://proj2-1095.appspot.com/UserAuth", "POST", "userName=" + Uname + "&passWord=" + Upass + "&Choice=Login", "authenticate_User",                                                    "POSTerror_handler");			
		}

		
		
    });
    
        /* button  Register */
    $(document).on("click", ".uib_w_79", function(evt)
    {
        /* your code goes here */ 
		Uname = document.getElementById("nameInput").value; 
		var Upass = document.getElementById("passInput").value;
		
		if (Uname === "" || Upass === "")
		{
			document.getElementById("authResponse").innerHTML = "Please fill out the fields";
		} else
		{		
			intel.xdk.device.getRemoteData("http://proj2-1095.appspot.com/UserAuth", "POST", "userName=" + Uname + "&passWord=" + Upass + "&Choice=Register", "register_User",                                                    "POSTerror_handler");
		}
    });
    
        /* button  New Study */
    $(document).on("click", ".uib_w_83", function(evt)
    {
         /*global activate_subpage */
         activate_subpage("#uib_page_4"); 
    });
    
        /* button  YOULIKETHAT */
    $(document).on("click", ".uib_w_84", function(evt)
    {
         /*global activate_subpage */
         activate_subpage("#uib_page_3"); 
    });
    
    }
	
	
    
        /* button  Return */
    $(document).on("click", ".uib_w_55", function(evt)
    {
         /*global activate_subpage */
         activate_subpage("#uib_page_2"); 
    });
    
    
        /* button  Back to resources */
    $(document).on("click", ".uib_w_56", function(evt)
    {
        /* your code goes here */ 

		//alert("HelloThere");
		navigator.geolocation.getCurrentPosition(onSuccess, onError);

    });
    
	 
	 
        /* button  Alert */
    $(document).on("click", ".uib_w_58", function(evt)
    {
        /* your code goes here */
		document.getElementById("frontPage").innerHTML = "Welcome to my Final Project, CS496 Fall 2015";
    });


    
        /* button  Get current studies */
    $(document).on("click", ".uib_w_59", function(evt)
    {
        /* your code goes here */ 
		intel.xdk.device.getRemoteData("http://proj2-1095.appspot.com/TimeStudies", "GET", "", "study_Results", "error_handler");
    });
    
        /* button  Button */
    $(document).on("click", ".uib_w_61", function(evt)
    {
        /* your code goes here */ 
		intel.xdk.device.getRemoteData("http://proj2-1095.appspot.com/studyProcedures", "GET", "", "procedure_Results", "error_handler");
    });
    
        /* button  .uib_w_62 */
    $(document).on("click", ".uib_w_62", function(evt)
    {
        /* your code goes here */ 
		intel.xdk.device.getRemoteData("http://proj2-1095.appspot.com/TSinstance" + "?user=" + Uname, "GET","", "instance_Results", "error_handler");
    });
    
        /* button  Secret! */
    $(document).on("click", ".uib_w_51", function(evt)
    {
         /*global activate_subpage */
         activate_subpage("#boobeer"); 
    });
    
        /* button  Clear */
    $(document).on("click", ".uib_w_63", function(evt)
    {
        /* your code goes here */ 
		document.getElementById("studyResults").innerHTML = "";
		document.getElementById("procedureResults").innerHTML = "";
		document.getElementById("instanceResults").innerHTML = "";
		document.getElementById("frontPage").innerHTML = "";
		document.getElementById("TimeDisplayBox").value = "";
		document.getElementById("endTime").value = "";
		document.getElementById("startTime").value = "";
    });
    
        /* button  Add a study */
    $(document).on("click", ".uib_w_64", function(evt)
    {
        /* your code goes here */ 
		var Tkeys = document.getElementById("studyKeys").value; 
		var Tname = document.getElementById("studyName").value;

		intel.xdk.device.getRemoteData("http://proj2-1095.appspot.com/TimeStudies", "POST", "name=" + Tname + "&procedures[]=" + Tkeys, "POSTsuccess_handler", "POSTerror_handler");
		
		document.getElementById("studyResults").innerHTML = "TimeStudy: " + Tname + "<br>was added succesfully with the following keys:" +
																		    "<br><br>" + Tkeys;
		
		
    });
    
        /* button  Add a Procedure */
    $(document).on("click", ".uib_w_68", function(evt)
    {
        /* your code goes here */ 
		var Pname = document.getElementById("procName").value; 
		var Piter = document.getElementById("procIter").value;
	    if (isNaN(Piter)) 
		{
			alert("Must input numbers");
			return false;
		} else
		{
		intel.xdk.device.getRemoteData("http://proj2-1095.appspot.com/studyProcedures", "POST", "name=" + Pname + "&iter=" + Piter, "POSTsuccess_handler", "POSTerror_handler");
		
		document.getElementById("procedureResults").innerHTML = "Procedure: " + Pname + "<br>was added succesfully running the following iteration:" +
																		    "<br><br>" + Piter;

		}		
    });
    
    /* button  Start a Study */
    $(document).on("click", ".uib_w_71", function(evt)
    {
        /* your code goes here */
		var Iname = document.getElementById("instName").value; 
		//get users location to input into the model
		var userLocation = navigator.geolocation.getCurrentPosition(onSuccess, onError);
		
	  //STILL NEED TO FIX THE GEOLOCATION, NOT RETURNING CORRECTLY
		intel.xdk.device.getRemoteData("http://proj2-1095.appspot.com/TSinstance", "POST", "name=" + Iname + "&user=" + 
									   Uname + "&location=" + userLocation, "POSTsuccess_handler", "POSTerror_handler");

		document.getElementById("instanceResults").innerHTML = "TA new instance of the TimeStudy " + Iname + "<br>was added succesfully";

		activate_subpage("#uib_page_3");
					
		

    });
	



    var onSuccess = function(position) 
	{  
		
		  userLocation =

          position.coords.latitude.toFixed(2)     +    ','   +
          position.coords.longitude.toFixed(2)    ;   
          /*'Altitude: '          + position.coords.altitude          + '\n' +
          'Accuracy: '          + position.coords.accuracy          + '\n' +
          'Altitude Accuracy: ' + position.coords.altitudeAccuracy  + '\n' +
          'Heading: '           + position.coords.heading           + '\n' +
          'Speed: '             + position.coords.speed             + "<br>" +
          'Timestamp: ' +"<br>" + position.timestamp                + "<br>";*/
		document.getElementById("frontPage").innerHTML = userLocation; 
		alert(typeof(userLocation));
     };
	

	
 document.addEventListener("app.Ready", register_event_handlers, false);
})();




        
    
function onError(error) {
    alert('code: '    + error.code    + '\n' +
          'message: ' + error.message + '\n');
    }
	
function study_Results(data) { document.getElementById("studyResults").innerHTML = "Current Existing TimeStudies: " + "<br>" + "<br>" + parseStudies(data); } 
function procedure_Results(data) { document.getElementById("procedureResults").innerHTML = "Current Existing TimeStudy Procedures: " + "<br>" + "<br>" + parseProcedures(data); } 
function instance_Results(data) { document.getElementById("instanceResults").innerHTML = "Current Existing TimeStudy Instances: " + "<br>" + "<br>" + parseInstances(data); } 
function error_handler(data) { alert("error: " + data); }
   


function parseProcedures(theData)
{
	//The variables procObjects splits the incoming data by the entity it is associated to in the 
	//Google App engine. We can then iterate through these entity's and extract the data that is needed.
	var procObjects = theData.split("StudyProcedures(key=Key('StudyProcedures', ");
	var re = /\d+/;
	var reName = /Pname=u'(.+?(?='))/;
	var reIter = /iteration=(.+?(?=,))/;
	var theKey = [];
	var procName = [];
	var iterCnt = [];
	var Statement = "";
	
	
	for(var i = 1; i < procObjects.length; i++)
	{
		theKey[i-1] = procObjects[i].match(re);
		procName[i-1] = procObjects[i].match(reName);
		iterCnt[i-1] = procObjects[i].match(reIter);
		Statement += "Procedure Name: " + procName[i-1][1] + "<br>" + 
					 "Your Key: "       + theKey[i-1]      + "<br>" + 
					 "Iteration: "      + iterCnt[i-1][1]  + "<br>" + "<br>";
	}
		
		
	return Statement;
}


function parseInstances(theData)
{
	//The variables procObjects splits the incoming data by the entity it is associated to in the 
	//Google App engine. We can then iterate through these entity's and extract the data that is needed.
	var procObjects = theData.split("TSInstance(key=Key('TSInstance', ");
	var re = /\d+/;
	var reName = /TSname=u'(.+?(?='))/;
	var reIter = /iteration=(.+?(?=,))/;
	var reUser = /user=u'(.+?(?='))/;
	var theKey = [];
	var studyName = [];
	var iterCnt = [];
	var userCnt = [];
	var Statement = "";
	
	
	for(var i = 1; i < procObjects.length; i++)
	{
		theKey[i-1] = procObjects[i].match(re);
		studyName[i-1] = procObjects[i].match(reName);
		iterCnt[i-1] = procObjects[i].match(reIter);
		userCnt[i-1] = procObjects[i].match(reUser);
		Statement += "Existing Instance: " + studyName[i-1][1] + "<br>" + 
					 "Your Key: "          + theKey[i-1]       + "<br>" + 
					 "Iteration: "         + iterCnt[i-1][1]   + "<br>" +
					 "User: "              + userCnt[i-1][1]   + "<br>" + "<br>";
	}
		
		
	return Statement;
}


function parseStudies(theData)
{
	//The variables procObjects splits the incoming data by the entity it is associated to in the 
	//Google App engine. We can then iterate through these entity's and extract the data that is needed.
	var procObjects = theData.split("TimeStudy(key=Key('TimeStudy', ");
	var re = /\d+/;
	var reName = /name=u'(.+?(?='))/;
	var reProcs = /s', (.+?(?=\)))/;
	var theKey = [];
	var studyName = [];
	var procKeys = [];
	var Statement = "";
	
	
	for(var i = 1; i < procObjects.length; i++)
	{
		theKey[i-1] = procObjects[i].match(re);
		studyName[i-1] = procObjects[i].match(reName);
		procKeys[i-1] = procObjects[i].match(reProcs);
		Statement += "Time Study: "           + studyName[i-1][1] + "<br>" + 
					 "TimeStudy Key: "        + theKey[i-1]       + "<br>" + 
					 "Procedure Keys: "       + procKeys[i-1][1]  + "<br>" + "<br>";
	}
		
		
	return Statement;
}



function authenticate_User(data)
{
	if (String(data) == "yes")
		{	

			
			var fragment = '<a class="widget uib_w_40 d-margins icon home" data-uib="app_framework/button" data-ver="1" href="#mainpage" data-transition="fade" id="Home_Pos1">Home</a><--Clickme';
// You can use native DOM methods to insert the fragment:
			document.getElementById("authResponse").innerHTML = fragment;
			activate_subpage("#mainpage"); //mainpage
		}
	else
		{
			
		document.getElementById("authResponse").innerHTML = "Incorrect Credentials";	
		}
	
		
		
	
		
}

function register_User(data)
{

	if (String(data) == "Registered")
		document.getElementById("authResponse").innerHTML = "It worked, please log in.";	
	if (String(data) == "nope")
		document.getElementById("authResponse").innerHTML = "Incorrect Credentials";
}


function POSTsuccess_handler (data) {  alert("success: " + data);
}
function POSTerror_handler(data) {  alert("error: " + data); }





















