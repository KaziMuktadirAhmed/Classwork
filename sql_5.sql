CREATE OR REPLACE FUNCTION annualS(p_value IN NUMBER, p_pct in NUMBER)

RETURN NUMBER IS

BEGIN

RETURN ((p_value + p_value*nvl(p_pct,0))*12);

END annualS;

/

SELECT employee_id, last_name, locations.country_id, annualS(salary,commission_pct) as "Annual Salary"
FROM employees,departments,locations
WHERE employees.department_id = departments.department_id and departments.location_id = locations.location_id and employee_id='100';