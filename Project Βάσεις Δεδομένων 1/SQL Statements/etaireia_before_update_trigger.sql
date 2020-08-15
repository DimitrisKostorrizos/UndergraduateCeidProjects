CREATE DEFINER = CURRENT_USER TRIGGER `erecruit`.`etaireia_BEFORE_UPDATE` BEFORE UPDATE ON `etaireia` FOR EACH ROW
BEGIN
	set new.AFM = old.AFM;
    set new.DOY = old.DOY;
    set new.name = old.name;
END