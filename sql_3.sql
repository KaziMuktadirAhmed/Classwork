create or replace procedure area_prod
(p_rad in NUMBER,
p_area out number)
is
begin
select 3.14*p_rad*p_rad into p_area from dual;
end area_prod;
/