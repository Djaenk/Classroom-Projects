(app => {

    const days = ['Monday', 'Tuesday', 'Wednesday', 'Thursday'];

    app.calendarView = {
        load(tutorId){
            let tutor = app.scheduler.getTutor(tutorId);
            document.querySelector("#schedule_name").innerText = tutor.name.toUpperCase();
            let table_element = document.querySelector("tbody");
            while(table_element.firstChild){
                table_element.removeChild(table_element.firstChild);
            }
            for(day of days){
                var row_element = document.createElement("tr");

                var day_element = document.createElement("td");
                day_element.innerText = day;
                row_element.appendChild(day_element);

                let appt = app.scheduler.getAppointment(tutorId, day);
                var appt_element = document.createElement("td");
                if(appt){
                    let name_element = document.createElement("h4");
                    name_element.innerText = appt.name;
                    appt_element.appendChild(name_element);

                    let notes_element = document.createElement("span");
                    notes_element.setAttribute("class", "notes");
                    notes_element.innerText = appt.notes;
                    appt_element.appendChild(notes_element);
                }
                else{
                    let button_element = document.createElement("button");
                    button_element.setAttribute("class", "enter");
                    button_element.setAttribute("onclick", `app.appointmentView.load(${tutorId}, "${day}")`);
                    button_element.innerText = "Book Appointment";
                    appt_element.appendChild(button_element);
                }
                row_element.appendChild(appt_element);

                table_element.appendChild(row_element);
            }
            app._changeView("calendarView");
        }
    };

})(app || (app = {}));