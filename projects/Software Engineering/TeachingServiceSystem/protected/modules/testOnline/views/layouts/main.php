<div id="menu">
	<?php 
	if(AccountComponent::getUserType()===UserAuthentication::TYPE_ADMIN|AccountComponent::getUserType()===UserAuthentication::TYPE_SYSTEM_ADMIN)
	{
		$this->renderPartial('/_listTeachers');
		$this->renderPartial('/_listStudents');
	}
	else
		$this->renderPartial('/_listCourses');
	?>
</div>