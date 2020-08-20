select candidate.username as Candidate_Name, candidate.certificates as Certificate_Filename, count(has_degree.degr_title) as Number_of_Degrees, avg(has_degree.grade) as Average_Grade
from candidate
inner join has_degree on candidate.username = has_degree.cand_usrname
group by has_degree.cand_usrname
having count(has_degree.degr_title) > 1