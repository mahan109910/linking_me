#include <QApplication>
#include <welcome.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// تعریف متغیر برای انتخاب زبان (جهت استفاده در Qt)
int selectedLanguage = 0;

// تابع main برای اجرای برنامه Qt
int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // ایجاد شیء QApplication
    welcome w; // ایجاد شیء welcome (باید در پروژه شما تعریف شده باشد)
    w.show(); // نمایش شیء welcome
    return a.exec(); // اجرای برنامه Qt
}

// تعریف کلاس Account
class Account {
public:
    std::string Account_ID; // شناسه حساب کاربری
    std::string Phone_number; // شماره تلفن
    std::string Email; // ایمیل
    std::vector<std::string> Connection; // لیست ارتباطات (شناسه‌ها)
    std::vector<std::string> following; // لیست دنبال‌کنندگان (شناسه‌ها)

    // سازنده کلاس Account
    Account(const std::string &id, const std::string &phone, const std::string &email)
        : Account_ID(id), Phone_number(phone), Email(email) {
        std::cout << "Account created" << std::endl;
    }

    // مخرب کلاس Account
    virtual ~Account() {
        std::cout << "Account destroyed" << std::endl;
    }

    // تابع افزودن ارتباط
    void addConnection(const std::string &id) {
        Connection.push_back(id);
    }

    // تابع افزودن دنبال‌کننده
    void addFollowing(const std::string &id) {
        following.push_back(id);
    }
};

// پیش‌تعریف کلاس Job
class Job;

// تعریف کلاس Person که از Account ارث‌بری می‌کند
class Person : public Account {
public:
    std::string Last_name; // نام خانوادگی
    std::string First_name; // نام
    std::vector<std::string> Skills; // لیست مهارت‌ها

    // سازنده کلاس Person
    Person(const std::string &id, const std::string &phone, const std::string &email, const std::string &lastName, const std::string &firstName)
        : Account(id, phone, email), Last_name(lastName), First_name(firstName) {
        std::cout << "Person created" << std::endl;
    }

    // مخرب کلاس Person
    ~Person() {
        std::cout << "Person destroyed" << std::endl;
    }

    // تابع گرفتن شغل
    void Take_Job(Job &job);
};

// تعریف کلاس Company که از Account ارث‌بری می‌کند
class Company : public Account {
public:
    std::vector<Job> company_jobs; // آرایه پویا از شغل‌ها
    std::string company_name; // نام شرکت
    std::vector<Person> employee; // آرایه پویا از کارمندان
    std::vector<std::string> followers; // لیست دنبال‌کنندگان

    // سازنده کلاس Company
    Company(const std::string &id, const std::string &phone, const std::string &email, const std::string &name)
        : Account(id, phone, email), company_name(name) {
        std::cout << "Company created" << std::endl;
    }

    // مخرب کلاس Company
    ~Company() {
        std::cout << "Company destroyed" << std::endl;
    }

    // تابع ایجاد شغل
    Job create_job();
};

// تعریف کلاس Job
class Job {
public:
    double salary; // حقوق
    std::string job_name; // نام شغل
    std::vector<std::string> skills_required; // مهارت‌های مورد نیاز
    std::string workPlace_type; // نوع محل کار
    std::string location; // مکان
    std::string type; // نوع شغل

    // سازنده کلاس Job
    Job(double sal, const std::string &job, const std::vector<std::string> &skills, const std::string &workPlace, const std::string &loc, const std::string &typ)
        : salary(sal), job_name(job), skills_required(skills), workPlace_type(workPlace), location(loc), type(typ) {
        std::cout << "Job created" << std::endl;
    }

    // مخرب کلاس Job
    ~Job() {
        std::cout << "Job destroyed" << std::endl;
    }
};

// پیاده‌سازی تابع create_job در کلاس Company
Job Company::create_job() {
    double salary = 50000;
    std::string job_name = "Software Engineer";
    std::vector<std::string> skills_required = {"C++", "Qt"};
    std::string workPlace_type = "Office";
    std::string location = "Tehran";
    std::string type = "Full-time";

    Job new_job(salary, job_name, skills_required, workPlace_type, location, type);
    company_jobs.push_back(new_job);
    return new_job;
}

// پیاده‌سازی تابع Take_Job در کلاس Person
void Person::Take_Job(Job &job) {
    std::cout << First_name << " " << Last_name << " took the job: " << job.job_name << std::endl;
}

// تعریف کلاس‌های مربوط به محتوا
class Time {
public:
    std::string day; // روز
    std::string month; // ماه
    std::string year; // سال
    std::string hour; // ساعت
    std::string minute; // دقیقه
    std::string second; // ثانیه

    // سازنده کلاس Time
    Time(const std::string &d, const std::string &m, const std::string &y,
         const std::string &h, const std::string &min, const std::string &s)
        : day(d), month(m), year(y), hour(h), minute(min), second(s) {}
};

class Content {
public:
    std::string sender_ID; // شناسه فرستنده
    Time time_sent; // زمان ارسال محتوا
    std::string Content_Text; // متن محتوا
    std::vector<std::string> attachments; // ضمیمه‌ها (نوشتاری، عکسی و یا فیلم)

    // سازنده کلاس Content
    Content(const std::string &sender, const Time &time, const std::string &text, const std::vector<std::string> &attach)
        : sender_ID(sender), time_sent(time), Content_Text(text), attachments(attach) {}
};

class Post : public Content {
public:
    std::string Post_ID; // شناسه پست
    int Repost_counter; // شمارنده تعداد بازنشر
    std::vector<std::string> Likes; // آرایه پویا از لایک‌ها
    std::vector<std::string> Comments; // آرایه پویا از کامنت‌ها

    // سازنده کلاس Post
    Post(const std::string &sender, const Time &time, const std::string &text, const std::vector<std::string> &attach, const std::string &post_id)
        : Content(sender, time, text, attach), Post_ID(post_id), Repost_counter(0) {}
};

class Comment : public Content {
public:
    std::string comment_ID; // شناسه کامنت
    std::string post_ID; // شناسه پست مربوط به کامنت

    // سازنده کلاس Comment
    Comment(const std::string &sender, const Time &time, const std::string &text, const std::vector<std::string> &attach, const std::string &comment_id, const std::string &post_id)
        : Content(sender, time, text, attach), comment_ID(comment_id), post_ID(post_id) {}
};

class Direct_Message : public Content {
public:
    std::string Message_ID; // شناسه پیام
    std::string To_who; // گیرنده پیام

    // سازنده کلاس Direct_Message
    Direct_Message(const std::string &sender, const Time &time, const std::string &text, const std::vector<std::string> &attach, const std::string &message_id, const std::string &to_who)
        : Content(sender, time, text, attach), Message_ID(message_id), To_who(to_who) {}
};

class Like {
public:
    std::string who_liked_ID; // شناسه کسی که لایک کرده
    std::string Like_ID; // شناسه لایک
    Time time; // زمان لایک کردن

    // سازنده کلاس Like
    Like(const std::string &who_liked, const std::string &like_id, const Time &time)
        : who_liked_ID(who_liked), Like_ID(like_id), time(time) {}
};
