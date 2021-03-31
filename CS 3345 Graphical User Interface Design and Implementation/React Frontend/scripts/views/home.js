(app => {

    var isLoaded = false;

    app.homeView = {
        load(){
            if(!isLoaded){
                let tutors = app.scheduler.getTutors()
                let tutors_list_element = document.querySelector("#tutors_list");
                for(tutor of tutors){
                    var tutor_element = document.createElement("li");

                    var img_element = document.createElement("img");
                    img_element.setAttribute("src", "http://placehold.it/150x150");
                    tutor_element.appendChild(img_element);

                    var tutor_name_element = document.createElement("h3");
                    tutor_name_element.innerText = tutor.name;
                    tutor_element.appendChild(tutor_name_element);

                    var button_element = document.createElement("button");
                    button_element.setAttribute("class", "enter");
                    button_element.setAttribute("onclick", `app.calendarView.load(${tutor.id})`);
                    button_element.innerText = "View Schedule";
                    tutor_element.appendChild(button_element);

                    var tutor_skills_element = document.createElement("ul");
                    tutor_skills_element.setAttribute("class", "skill_list");
                    for(skill of tutor.skills){
                        var skill_element = document.createElement("li");
                        skill_element.innerText = skill;
                        tutor_skills_element.appendChild(skill_element);
                    }
                    tutor_element.appendChild(tutor_skills_element);

                    tutors_list_element.appendChild(tutor_element);
                }
                isLoaded = true;
            }
            app._changeView("homeView");
        }
    }

})(app || (app = {}));