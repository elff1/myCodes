    <div class="row">
		<?php echo $form->labelEx($personalInfoModel,'first_name'); ?>
		<?php echo $form->textField($personalInfoModel,'first_name',array('size'=>8,'maxlength'=>8)); ?>
		<?php echo $form->error($personalInfoModel,'first_name'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($personalInfoModel,'last_name'); ?>
		<?php echo $form->textField($personalInfoModel,'last_name',array('size'=>8,'maxlength'=>8)); ?>
		<?php echo $form->error($personalInfoModel,'last_name'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($personalInfoModel,'sex'); ?>
		<?php echo $form->dropDownList($personalInfoModel,'sex',$personalInfoModel->genderOptions); ?>
		<?php echo $form->error($personalInfoModel,'sex'); ?>
	</div>
	
	<div class="row">
		<?php echo $form->labelEx($personalInfoModel,'image'); ?>
		<?php echo $form->fileField($personalInfoModel,'image'); ?>
		<?php echo $form->error($personalInfoModel,'image'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($personalInfoModel,'date_of_birth'); ?>		
		<?php $this->widget('zii.widgets.jui.CJuiDatePicker', array(  

        'attribute' => 'date_of_birth',  
        'model'=>$personalInfoModel,
        'options' => array(
                'dateFormat' => 'yy-mm-dd',  

        ),
		));?>
		
		<?php echo $form->error($personalInfoModel,'date_of_birth'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($personalInfoModel,'ethnic_group'); ?>
		<?php echo $form->dropDownList($personalInfoModel,'ethnic_group', $personalInfoModel->ethnicGroupList); ?>
		<?php echo $form->error($personalInfoModel,'ethnic_group'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($personalInfoModel,'political_status'); ?>
		<?php echo $form->dropDownList($personalInfoModel,'political_status', $personalInfoModel->politicalStatusList); ?>
		<?php echo $form->error($personalInfoModel,'political_status'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($personalInfoModel,'birth_place_city'); ?>
		<?php echo $form->dropDownList($personalInfoModel,'birth_place_city',$personalInfoModel->getCityList($personalInfoModel->birth_place_province)); ?>
		<?php echo $form->error($personalInfoModel,'birth_place_city'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($personalInfoModel,'birth_place_province'); ?>
		<?php echo $form->dropDownList($personalInfoModel,'birth_place_province',$personalInfoModel->provinceList, 
		array(
			'ajax'=>array(
				'url'=>$this->createUrl('personalInfo/dynamicCity'),
				'data'=>array('pid'=>'js:this.value'),
				'update'=>'#'.CHtml::activeId($personalInfoModel,'birth_place_city'),
				),
			)
			
		); ?>
		<?php echo $form->error($personalInfoModel,'birth_place_province'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($personalInfoModel,'original_residence_city'); ?>
		<?php echo $form->dropDownList($personalInfoModel,'original_residence_city',$personalInfoModel->getCityList($personalInfoModel->original_residence_province)); ?>
		<?php echo $form->error($personalInfoModel,'original_residence_city'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($personalInfoModel,'original_residence_province'); ?>
		<?php echo $form->dropDownList($personalInfoModel,'original_residence_province',$personalInfoModel->provinceList, 
		array(
			'ajax'=>array(
				'url'=>$this->createUrl('personalInfo/dynamicCity'),
				'data'=>array('pid'=>'js:this.value'),
				'update'=>'#'.CHtml::activeId($personalInfoModel,'original_residence_city'),
				),
			)
			
		); ?>
		<?php echo $form->error($personalInfoModel,'original_residence_province'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($personalInfoModel,'home_address'); ?>
		<?php echo $form->textField($personalInfoModel,'home_address',array('size'=>60,'maxlength'=>64)); ?>
		<?php echo $form->error($personalInfoModel,'home_address'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($personalInfoModel,'home_postcode'); ?>
		<?php echo $form->textField($personalInfoModel,'home_postcode',array('size'=>6,'maxlength'=>6)); ?>
		<?php echo $form->error($personalInfoModel,'home_postcode'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($personalInfoModel,'home_phone'); ?>
		<?php echo $form->textField($personalInfoModel,'home_phone',array('size'=>32,'maxlength'=>32)); ?>
		<?php echo $form->error($personalInfoModel,'home_phone'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($personalInfoModel,'email'); ?>
		<?php echo $form->textField($personalInfoModel,'email',array('size'=>60,'maxlength'=>64)); ?>
		<?php echo $form->error($personalInfoModel,'email'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($personalInfoModel,'phone'); ?>
		格式: XXX(X)-XXXXXXX(X) | XXXXXXXXXXXXX<br/>
		<?php echo $form->textField($personalInfoModel,'phone',array('size'=>32,'maxlength'=>32)); ?>
		<?php echo $form->error($personalInfoModel,'phone'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($personalInfoModel,'identity_card_number'); ?>
		<?php echo $form->textField($personalInfoModel,'identity_card_number',array('size'=>18,'maxlength'=>18)); ?>
		<?php echo $form->error($personalInfoModel,'identity_card_number'); ?>
	</div>