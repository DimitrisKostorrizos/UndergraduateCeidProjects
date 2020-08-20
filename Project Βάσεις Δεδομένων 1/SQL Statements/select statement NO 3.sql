select candidate.username as Candidate_Username, count(applies.cand_usrname) as Number_of_Applications, avg(job.salary) as Average_Salary
from candidate
inner join applies on candidate.username = applies.cand_usrname
inner join job on applies.job_id = job.id
group by candidate.username
having avg(job.salary) > 1800