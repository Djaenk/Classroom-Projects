(app => {

    class Tutor {
        constructor(id, name, skills){
            this.id = id;
            this.name = name;
            this.skills = skills;
        }
    }

    class Appointment {
        constructor(tutorId, day, name, notes){
            this.tutorId = tutorId;
            this.day = day;
            this.name = name;
            this.notes = notes;
        }
    }

    app.Tutor = Tutor;
    app.Appointment = Appointment;

    const tutors = [
        new Tutor(1, "John", [".NET", "Angular"]),
        new Tutor(2, "David", ["React", "Node"]),
        new Tutor(3, "Karen", ["Angular", "View"]),
        new Tutor(4, "Janet", ["REST Services", "SQL"]),
        new Tutor(5, "David", [".NET"])
    ];

    let appointments = [
        new Appointment(1, 'Monday', 'Sally', 'I need lots of Angular help!')
    ];

    app.scheduler = {
        getTutors(){
            return tutors;
        },

        getTutor(tutorId){
            for(tutor of tutors){
                if(tutor.id == tutorId){
                    return tutor;
                }
            }
        },

        getAppointments(){
            return appointments;
        },

        getAppointment(tutorId, day){
            for(appt of appointments){
                if(appt.tutorId == tutorId && appt.day == day){
                    return appt;
                }
            }
        },

        saveAppointment(tutorId, day, name, notes){
            appointments.push(new Appointment(tutorId, day, name, notes));
        }
    }

})(app || (app = {}));