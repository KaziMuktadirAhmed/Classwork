create or replace function get_area(radius in number) 
return number is
	begin
        	return  3.14159265358979* radius*radius;
       end get_area;
/