#include <QApplication>
#include <welcome.h>
#include <iostream>
#include <vector>
#include <string>
//#include <curl/curl.h>
#include <map>

using namespace std;

// تعریف متغیر برای انتخاب زبان (جهت استفاده در Qt)
int selectedLanguage = 0;

// تابع main برای اجرای برنامه Qt
int main(int argc, char *argv[]) {
    QApplication a(argc, argv); // ایجاد شیء QApplication
    welcome w; // ایجاد شیء welcome (باید در پروژه شما تعریف شده باشد)
    w.show(); // نمایش شیء welcome
    return a.exec(); // اجرای برنامه Qt
}

//////////////////شروع کلاس های پست

// تعریف کلاس Time
class Time {
public:
    std::string day;
    std::string month;
    std::string year;
    std::string hour;
    std::string minute;
    std::string second;

    Time(const std::string &d, const std::string &m, const std::string &y,
         const std::string &h, const std::string &min, const std::string &s)
        : day(d), month(m), year(y), hour(h), minute(min), second(s) {}
};

// تعریف کلاس Like
class Like {
public:
    std::string how_like_id;
    std::string like_id;
    Time time;

    Like(const std::string &hl_id, const std::string &l_id, const Time &t)
        : how_like_id(hl_id), like_id(l_id), time(t) {}
};

// تعریف کلاس Content
class Content {
public:
    std::string sender_ID;
    Time time_sent;
    std::string Content_Text;
    std::vector<std::string> Content_picture;
    std::vector<std::string> Content_video;

    Content(const std::string &sender, const Time &time, const std::string &text,
            const std::vector<std::string> &picture, const std::vector<std::string> &video)
        : sender_ID(sender), time_sent(time), Content_Text(text),
        Content_picture(picture), Content_video(video) {}
};

// تعریف کلاس Direct_Message که از Content ارث‌بری می‌کند
class Direct_Message : public Content {
public:
    std::string Message_ID;
    std::string To_who;

    Direct_Message(const std::string &sender, const Time &time, const std::string &text,
                   const std::vector<std::string> &picture, const std::vector<std::string> &video,
                   const std::string &message_id, const std::string &to_who)
        : Content(sender, time, text, picture, video), Message_ID(message_id), To_who(to_who) {}

    ~Direct_Message() {
        std::cout << "Direct_Message destroyed" << std::endl;
    }
};

// تعریف کلاس Comment که از Content ارث‌بری می‌کند
class Comment : public Content {
public:
    std::string post_ID;
    std::string comment_ID;

    Comment(const std::string &sender, const Time &time, const std::string &text,
            const std::vector<std::string> &picture, const std::vector<std::string> &video,
            const std::string &post_id, const std::string &comment_id)
        : Content(sender, time, text, picture, video), post_ID(post_id), comment_ID(comment_id) {}
};

// تعریف کلاس Post که از Content ارث‌بری می‌کند
class Post : public Content {
public:
    std::string Post_ID;
    int Repost_counter;
    std::vector<Like> Likes;
    std::vector<Comment> Comments;

    Post(const std::string &sender, const Time &time, const std::string &text,
         const std::vector<std::string> &picture, const std::vector<std::string> &video,
         const std::string &post_id)
        : Content(sender, time, text, picture, video), Post_ID(post_id), Repost_counter(0) {}

    ~Post() {
        std::cout << "Post destroyed" << std::endl;
    }
};

//////////////////شروع کلاس های ثبت نام و اطلاعات کاربر

// تعریف کلاس Job
class Job {
public:
    double salary;
    std::string job_name;
    std::string company_name;
    std::vector<std::string> skills_required;
    std::string workPlace_type;
    std::string location;
    std::string type;

    Job(double sal, const std::string &job, const std::string &company,
        const std::vector<std::string> &skills, const std::string &workplace,
        const std::string &loc, const std::string &t)
        : salary(sal), job_name(job), company_name(company), skills_required(skills),
        workPlace_type(workplace), location(loc), type(t) {
        std::cout << "Job created" << std::endl;
    }

    ~Job() {
        std::cout << "Job destroyed" << std::endl;
    }
};

// تعریف کلاس Account
class Account {
public:
    std::string Account_ID;
    std::string Phone_number;
    std::string Email;
    std::vector<std::string> Connection;
    std::vector<std::string> following;
    std::vector<Direct_Message> DM; // آرایه دینامیک از پیام‌ها
    std::vector<Post> Posts; // آرایه دینامیک از پست‌ها

    Account(const std::string &id, const std::string &phone, const std::string &email)
        : Account_ID(id), Phone_number(phone), Email(email) {
        std::cout << "Account created" << std::endl;
    }

    virtual ~Account() {
        std::cout << "Account destroyed" << std::endl;
    }

    void addConnection(const std::string &id) {
        Connection.push_back(id);
    }

    void addFollowing(const std::string &id) {
        following.push_back(id);
    }

    void addDM(const Direct_Message &message) {
        DM.push_back(message);
    }

    void addPost(const Post &post) {
        Posts.push_back(post);
    }
};

// تعریف کلاس Person که از Account ارث‌بری می‌کند
class Person : public Account {
public:
    std::string Last_name;
    std::string First_name;
    std::vector<std::string> Skills;

    Person(const std::string &id, const std::string &phone, const std::string &email,
           const std::string &lastName, const std::string &firstName)
        : Account(id, phone, email), Last_name(lastName), First_name(firstName) {
        std::cout << "Person created" << std::endl;
    }

    ~Person() {
        std::cout << "Person destroyed" << std::endl;
    }

    void addSkill(const std::string &skill) {
        Skills.push_back(skill);
    }

    void Take_Job(Job &job);
};

// تعریف کلاس Company که از Account ارث‌بری می‌کند
class Company : public Account {
public:
    std::vector<Job> company_jobs;
    std::string company_name;
    std::vector<Person> employees;
    std::vector<std::string> followers;

    Company(const std::string &id, const std::string &phone, const std::string &email,
            const std::string &name)
        : Account(id, phone, email), company_name(name) {
        std::cout << "Company created" << std::endl;
    }

    ~Company() {
        std::cout << "Company destroyed" << std::endl;
    }

    Job create_job(double salary, const std::string &job_name, const std::string &company_name,
                   const std::vector<std::string> &skills_required, const std::string &workPlace_type,
                   const std::string &location, const std::string &type) {
        Job new_job(salary, job_name, company_name, skills_required, workPlace_type, location, type);
        company_jobs.push_back(new_job);
        return new_job;
    }

    void addEmployee(const Person &employee) {
        employees.push_back(employee);
    }

    void addFollower(const std::string &follower_id) {
        followers.push_back(follower_id);
    }
};

// پیاده‌سازی تابع Take_Job در کلاس Person
void Person::Take_Job(Job &job) {
    std::cout << First_name << " " << Last_name << " took the job: " << job.job_name << std::endl;
}

// تابع ارسال ایمیل
/*bool sendEmail(const std::string &recipient, const std::string &subject, const std::string &body) {
    CURL *curl;
    CURLcode res = CURLE_OK;
    struct curl_slist *recipients = NULL;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_USERNAME, "mahan.test.h@gmail.com");
        curl_easy_setopt(curl, CURLOPT_PASSWORD, "vxbe qlgu evid fdux");
        curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.gmail.com:587");
        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, "<mahan.test.h@gmail.com>");

        recipients = curl_slist_append(recipients, recipient.c_str());
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

        std::string data = "To: " + recipient + "\r\n" +
                           "From: <mahan.test.h@gmail.com>\r\n" +
                           "Subject: " + subject + "\r\n" +
                           "\r\n" + body + "\r\n";

        curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_READDATA, &data);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
    }

    return (res == CURLE_OK);
}*/
