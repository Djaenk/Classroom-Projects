(app => {

    let selected = [];

    app.appointmentView = {
        load(tutorId, day){
            selected.tutorId = tutorId;
            selected.day = day;
            app._changeView("appointmentView");
        },

        save(){
            let input_element = document.querySelector("input");
            let textarea_element = document.querySelector("textarea");
            app.scheduler.saveAppointment(selected.tutorId, selected.day, input_element.value, textarea_element.value);
            document.forms["appointment_form"].reset();
            app.calendarView.load(selected.tutorId);
        }
    };

})(app || (app = {}));