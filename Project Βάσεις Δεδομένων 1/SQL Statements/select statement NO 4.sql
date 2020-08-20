select etaireia.name as Company_Name, job.position as Job, antikeim.title as Workpiece
from etaireia
inner join recruiter on etaireia.AFM = recruiter.firm
inner join job on job.recruiter = recruiter.username
inner join requires on job.id = requires.job_id
inner join antikeim on requires.antikeim_title = antikeim.title
where (etaireia.city = "Patra") AND (antikeim.title like "%Program%")