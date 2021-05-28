create or replace function annual_sal(p_salary in number, p_commission in number)
return number is
begin
return (p_salary+p_salary*nvl(p_commission,0))*12;
end annual_sal;
/

select employee_id, last_name, salary, annual_sal(salary,commission_pct) "Anual Salary" 
from employees
where department_id=100;