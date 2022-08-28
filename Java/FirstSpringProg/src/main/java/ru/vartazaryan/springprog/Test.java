package ru.vartazaryan.springprog;

import org.springframework.context.support.ClassPathXmlApplicationContext;

public class Test
{
    public static void main(String[] args)
    {
        ClassPathXmlApplicationContext context = new ClassPathXmlApplicationContext(
                "applicationContext.xml"
        );

        FirstBean bean = context.getBean("testBean", FirstBean.class);

        System.out.println(bean.getName());

        context.close();
    }
}
